#include "../../incs/cub3d.h"

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

static void	dda(t_core *core)
{
	int	hit;

	hit = 0;
	core->ray.side = 0; // 0 = hit x-side, 1 = hit y-sid,
	while (!hit)
	{
		if (core->ray.side_dist_x < core->ray.side_dist_y)
		{
			core->ray.side_dist_x += core->ray.delta_dist_x;
			core->ray.map_x += core->ray.step_x;
			core->ray.side = 0;
		}
		else
		{
			core->ray.side_dist_y += core->ray.delta_dist_y;
			core->ray.map_y += core->ray.step_y;
			core->ray.side = 1;
		}
		if (is_wall(core, core->ray.map_x, core->ray.map_y))
			hit = 1;
	}
}

static void	calc_perp_wall_dist(t_core *core)
{
	if (core->ray.side == 0)
		core->ray.perp_wall_dist = (core->ray.side_dist_x - core->ray.delta_dist_x);
	else
		core->ray.perp_wall_dist = (core->ray.side_dist_y - core->ray.delta_dist_y);

	if (core->ray.perp_wall_dist <= 0.1)
		core->ray.perp_wall_dist = 0.1;
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

int	get_pixel_from_texture(t_img *img, int tex_x, int tex_y)
{
	char	*pixel;
	int		bpp;

	if (!img || !img->addr || img->width <= 0 || img->height <= 0)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	if (tex_y >= img->height)
		tex_y = img->height - 1;
	bpp = img->bpp / 8;
	pixel = img->addr + (tex_y * img->line_len + tex_x * bpp);
	return (*(int *)pixel);
}

static void	get_texture(t_core *core)
{
	t_img	*tex;

	if (core->ray.side == 0)
	{
		if (core->ray.ray_dir_x > 0)
			tex = &core->textures.we_img;
		else
			tex = &core->textures.ea_img;
	}
	else
	{
		if (core->ray.ray_dir_y > 0)
			tex = &core->textures.no_img;
		else
			tex = &core->textures.so_img;
	}
	core->ray.tex = tex;
}

static void	calc_tex_x(t_core *core)
{
	int	tex_x;
	double	wall_x;
	t_img	*tex;

	wall_x = core->ray.wall_x;
	tex = core->ray.tex;
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if(core->ray.side == 0 && core->ray.ray_dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if(core->ray.side == 1 && core->ray.ray_dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	core->ray.tex_x = tex_x;
}

static inline unsigned int	get_tex_pixel(t_img *tex, int tex_x, int tex_y)
{
	char	*dst;

	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	calc_wall_x(t_core *core)
{
	double	wall_x;
	
	if (core->ray.side == 0)
		wall_x = core->player.y + core->ray.perp_wall_dist * core->ray.ray_dir_y;
	else
		wall_x = core->player.x + core->ray.perp_wall_dist * core->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	core->ray.wall_x = wall_x;
}

void	get_draw_info(t_core *core)
{
	core->ray.true_draw_start = -core->ray.line_height / 2 + HEIGHT / 2;
	core->ray.draw_step = (double)core->ray.tex->height / (double)(core->ray.line_height);
}

void	draw_vertical_texture(t_core *core, int x, int draw_start, int draw_end)
{
	int		tex_y;
	int		y;
	float	tex_pos;
	
	if (x < 0 || x >= WIDTH || draw_start > draw_end)
		return;
	tex_pos = (draw_start - core->ray.true_draw_start) * core->ray.draw_step;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= core->ray.tex->height)
			tex_y = core->ray.tex->height - 1;
		put_pixel(core, x, y, get_tex_pixel(core->ray.tex, core->ray.tex_x, tex_y));
		tex_pos += core->ray.draw_step;
		y++;
	}
}

void	calc_wall_slice(t_core *core)
{
	int	half;

	half = (int)(HEIGHT / core->ray.perp_wall_dist) / 2;
	core->ray.draw_start = HEIGHT / 2 - half;
	core->ray.draw_end = HEIGHT / 2 + half;
	if (core->ray.draw_start < 0)
		core->ray.draw_start = 0;
	if (core->ray.draw_end >= HEIGHT)
		core->ray.draw_end = HEIGHT - 1;
	core->ray.line_height = half * 2;
}

static void	draw_to_screen(t_core *core, int x)
{
	calc_wall_slice(core);
	calc_wall_x(core); 
	get_texture(core);
	calc_tex_x(core);
	get_draw_info(core);
	draw_vertical(core, x, 0, core->ray.draw_start - 1, core->textures.ceiling_int);
	draw_vertical_texture(core, x, core->ray.draw_start, core->ray.draw_end);
	draw_vertical(core, x, core->ray.draw_end + 1, HEIGHT - 1, core->textures.floor_int);
}

void	draw_3d(t_core *core)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(core, x);
		set_step(core);
		dda(core);
		calc_perp_wall_dist(core);
		core->zbuffer[x] = core->ray.perp_wall_dist;
		draw_to_screen(core, x);
		x++;
	}
}
