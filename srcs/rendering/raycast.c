#include "../../incs/cub3d.h"

static int	shade_color(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255) b = 255;
	return ((r << 16) | (g << 8) | b);
}

static void	draw_vertical(t_core *core, int x, int y0, int y1, int color)
{
	int	y;

	if (x < 0 || x >= WIDTH)
		return;
	if (y0 < 0)
		y0 = 0;
	if (y1 >= HEIGHT)
		y1 = HEIGHT - 1;
	y = y0;
	while (y <= y1)
		put_pixel(core, x, y++, color);
}

static int	is_wall(t_core *core, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
	/* row length may be smaller than map.width; treat outside as wall */
	if ((int)ft_strlen(core->map.grid[map_y]) <= map_x)
		return (1);
	return (core->map.grid[map_y][map_x] == '1');
}

void	draw_3d(t_core *core)
{
	int		x;
	int		ceil_color;
	int		floor_color;

	ceil_color = rgb_to_int(core->textures.ceiling);
	floor_color = rgb_to_int(core->textures.floor);

	x = 0;
	while (x < WIDTH)
	{
		/* 1) Ray setup */
		double	camera_x = 2.0 * x / (double)WIDTH - 1.0;
		double	ray_dir_x = core->player.dir_x + core->player.plane_x * camera_x;
		double	ray_dir_y = core->player.dir_y + core->player.plane_y * camera_x;

		int		map_x = (int)core->player.x;
		int		map_y = (int)core->player.y;

		double	delta_dist_x = (ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / ray_dir_y);

		int		step_x;
		int		step_y;
		double	side_dist_x;
		double	side_dist_y;

		/* 2) Step + initial sideDist */
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (core->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - core->player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (core->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - core->player.y) * delta_dist_y;
		}

		/* 3) DDA */
		int	hit = 0;
		int	side = 0; /* 0 = hit x-side, 1 = hit y-side */
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (is_wall(core, map_x, map_y))
				hit = 1;
		}

		/* 4) Perpendicular distance (prevents fish-eye) */
		double	perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		if (perp_wall_dist <= 0.0001)
			perp_wall_dist = 0.0001;

		/* 5) Project to screen: line height */
		int	line_height = (int)(HEIGHT / perp_wall_dist);

		int	draw_start = -line_height / 2 + HEIGHT / 2;
		int	draw_end = line_height / 2 + HEIGHT / 2;

		/* 6) Colors (simple) */
		int	wall_color = 0x00FFFFFF; /* white */
		if (side == 1)
			wall_color = shade_color(wall_color, 0.70f); /* darken y-sides */

		/* 7) Draw ceiling, wall, floor */
		draw_vertical(core, x, 0, draw_start - 1, ceil_color);
		draw_vertical(core, x, draw_start, draw_end, wall_color);
		draw_vertical(core, x, draw_end + 1, HEIGHT - 1, floor_color);

		x++;
	}
}
