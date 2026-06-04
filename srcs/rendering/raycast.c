#include "../../incs/cub3d.h"

static int	shade_color(int color, float factor) // TODO debug only delete later
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

static void	setup_ray(t_core *core, int x)
{
	core->ray.camera_x = 2.0 * x / (double)WIDTH - 1.0;
	core->ray.ray_dir_x = core->player.dir_x + core->player.plane_x * core->ray.camera_x;
	core->ray.ray_dir_y = core->player.dir_y + core->player.plane_y * core->ray.camera_x;
	core->ray.map_x = (int)core->player.x;
	core->ray.map_y = (int)core->player.y;
	core->ray.delta_dist_x = (core->ray.ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / core->ray.ray_dir_x);
	core->ray.delta_dist_y = (core->ray.ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / core->ray.ray_dir_y);
}

static void	set_step(t_core *core)
{
	if (core->ray.ray_dir_x < 0)
	{
		core->ray.step_x = -1;
		core->ray.side_dist_x = (core->player.x - core->ray.map_x) * core->ray.delta_dist_x;
	}
	else
	{
		core->ray.step_x = 1;
		core->ray.side_dist_x = (core->ray.map_x + 1.0 - core->player.x) * core->ray.delta_dist_x;
	}
	if (core->ray.ray_dir_y < 0)
	{
		core->ray.step_y = -1;
		core->ray.side_dist_y = (core->player.y - core->ray.map_y) * core->ray.delta_dist_y;
	}
	else
	{
		core->ray.step_y = 1;
		core->ray.side_dist_y = (core->ray.map_y + 1.0 - core->player.y) * core->ray.delta_dist_y;
	}
}

static int	dda(t_core *core)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0; // 0 = hit x-side, 1 = hit y-sid,
	while (!hit)
	{
		if (core->ray.side_dist_x < core->ray.side_dist_y)
		{
			core->ray.side_dist_x += core->ray.delta_dist_x;
			core->ray.map_x += core->ray.step_x;
			side = 0;
		}
		else
		{
			core->ray.side_dist_y += core->ray.delta_dist_y;
			core->ray.map_y += core->ray.step_y;
			side = 1;
		}
		if (is_wall(core, core->ray.map_x, core->ray.map_y))
			hit = 1;
	}
	return (side);
}

static double	calc_perp_wall_dist(t_core *core, int side)
{
	double	perp_wall_dist;

	if (side == 0)
		perp_wall_dist = (core->ray.side_dist_x - core->ray.delta_dist_x);
	else
		perp_wall_dist = (core->ray.side_dist_y - core->ray.delta_dist_y);

	if (perp_wall_dist <= 0.0001)
		perp_wall_dist = 0.0001;
	return (perp_wall_dist);
}

static void	draw_to_screen(t_core *core, double perp_wall_dist, int x, int side)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	ceil_color;
	int	floor_color;

	ceil_color = rgb_to_int(core->textures.ceiling);
	floor_color = rgb_to_int(core->textures.floor);
	line_height = (int)(HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;

	/* 6) Colors (simple) */
	int	wall_color = 0x00FFFFFF; /* white */
	if (side == 1)
		wall_color = shade_color(wall_color, 0.70f); /* darken y-sides */

	/* 7) Draw ceiling, wall, floor */
	draw_vertical(core, x, 0, draw_start - 1, ceil_color);
	draw_vertical(core, x, draw_start, draw_end, wall_color);
	draw_vertical(core, x, draw_end + 1, HEIGHT - 1, floor_color);
}

void	draw_3d(t_core *core)
{
	int		x;
	int		side;
	double	perp_wall_dist;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(core, x);
		set_step(core);
		side = dda(core);
		perp_wall_dist = calc_perp_wall_dist(core, side);
		draw_to_screen(core, perp_wall_dist, x, side);
		x++;
	}
}
