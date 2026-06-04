#include "../../incs/cub3d.h"

static int	get_texture_pixel(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= img->width)
		x = img->width - 1;
	if (y < 0)
		y = 0;
	if (y >= img->height)
		y = img->height - 1;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

static t_img	*select_texture(t_core *core, int side)
{
	if (side == 0)
	{
		if (core->ray.ray_dir_x > 0)
			return (&core->textures.we_img);
		return (&core->textures.ea_img);
	}
	if (core->ray.ray_dir_y > 0)
		return (&core->textures.no_img);
	return (&core->textures.so_img);
}

static int	is_wall(t_core *core, int map_x, int map_y)
{
	return (get_map_cell(core, map_x, map_y) == '1');
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
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	double	wall_x;
	double	tex_pos;
	double	step;
	t_img	*tex;

	ceil_color = rgb_to_int(core->textures.ceiling);
	floor_color = rgb_to_int(core->textures.floor);
	line_height = (int)(HEIGHT / perp_wall_dist);
	if (line_height < 1)
		line_height = 1;
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (side == 0)
		wall_x = core->player.y + perp_wall_dist * core->ray.ray_dir_y;
	else
		wall_x = core->player.x + perp_wall_dist * core->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex = select_texture(core, side);
	tex_x = (int)(wall_x * (double)tex->width);
	if (side == 0 && core->ray.ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (side == 1 && core->ray.ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = 0;
	while (y < draw_start)
		put_pixel(core, x, y++, ceil_color);
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(core, x, y, color);
		y++;
	}
	y = draw_end + 1;
	while (y < HEIGHT)
		put_pixel(core, x, y++, floor_color);
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
