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

static int	is_wall(t_core *core, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
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
	core->ray.side = 0;
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

t_img	*get_texture(t_core *core)
{
	if (core->ray.side == 0)
	{
		if (core->ray.ray_dir_x > 0)
			return (&core->textures.we_img);
		else
			return (&core->textures.ea_img);
	}
	else
	{
		if (core->ray.ray_dir_y > 0)
			return (&core->textures.no_img);
		else
			return (&core->textures.so_img);
	}
}

int	get_tex_x(t_core *core, double wall_x, t_img *tex)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (core->ray.side == 0 && core->ray.ray_dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if (core->ray.side == 1 && core->ray.ray_dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static inline unsigned int	get_tex_pixel(t_img *tex, int tex_x, int tex_y)
{
	char	*dst;

	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

/*
** Psychedelic wall effect:
**   1. Warp tex_x and tex_y using sine-table waves (no math.h sin per pixel)
**   2. Palette cycle: shift RGB channels at different speeds
*/
void	draw_vertical_texture(t_core *core, int x, int draw_start, int draw_end)
{
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			warped_x;
	int			warped_y;
	int			y;
	t_img		*tex;
	double		step;
	float		tex_pos;
	int			line_height;
	int			true_draw_start;
	float		t;
	unsigned int	color;
	int			r, g, b;
	int			shift;

	if (x < 0 || x >= WIDTH || draw_start > draw_end)
		return ;
	if (core->ray.side == 0)
		wall_x = core->player.y + core->ray.perp_wall_dist * core->ray.ray_dir_y;
	else
		wall_x = core->player.x + core->ray.perp_wall_dist * core->ray.ray_dir_x;
	wall_x -= floor(wall_x);

	tex				= get_texture(core);
	tex_x			= get_tex_x(core, wall_x, tex);
	line_height		= (int)(HEIGHT / core->ray.perp_wall_dist);
	true_draw_start	= -line_height / 2 + HEIGHT / 2;
	step			= (double)tex->height / (double)line_height;
	tex_pos			= (draw_start - true_draw_start) * step;

	/* time index scaled into table units */
	t = (float)core->anim_tick * ((float)SIN_TABLE_SIZE * 0.07f / (2.0f * (float)M_PI));

	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;

		/* --- WARP: two-wave interference on both axes --- */
		warped_x = tex_x
			+ (int)(LSIN(core, (int)(tex_y * 0.08f * SIN_TABLE_SIZE / (2.0f * (float)M_PI)) + (int)t) * 12.0f)
			+ (int)(LSIN(core, (int)(tex_y * 0.03f * SIN_TABLE_SIZE / (2.0f * (float)M_PI)) - (int)(t * 1.3f)) * 8.0f);
		warped_y = tex_y
			+ (int)(LCOS(core, (int)(tex_x * 0.10f * SIN_TABLE_SIZE / (2.0f * (float)M_PI)) + (int)(t * 0.9f)) * 10.0f)
			+ (int)(LCOS(core, (int)(y    * 0.05f * SIN_TABLE_SIZE / (2.0f * (float)M_PI)) + (int)(t * 1.7f)) * 6.0f);

		/* wrap into texture bounds */
		warped_x = ((warped_x % tex->width)  + tex->width)  % tex->width;
		warped_y = ((warped_y % tex->height) + tex->height) % tex->height;

		color = get_tex_pixel(tex, warped_x, warped_y);

		/* --- PALETTE CYCLE: shift RGB channels at different speeds --- */
		shift = (int)(core->anim_tick * 2) & 0xFF;
		r = (int)(((color >> 16) & 0xFF) + shift)        & 0xFF;
		g = (int)(((color >> 8)  & 0xFF) + shift * 2)    & 0xFF;
		b = (int)((color         & 0xFF) + shift * 3)     & 0xFF;
		color = ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;

		put_pixel(core, x, y, (int)color);
		tex_pos += step;
		y++;
	}
}

static void	draw_to_screen(t_core *core, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	ceil_color;
	int	floor_color;
	int	wall_color;

	ceil_color	= rgb_to_int(core->textures.ceiling);
	floor_color	= rgb_to_int(core->textures.floor);
	line_height	= (int)(HEIGHT / core->ray.perp_wall_dist);
	draw_start	= -line_height / 2 + HEIGHT / 2;
	draw_end	= line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	wall_color = 0x00FFFFFF;
	if (core->ray.side == 1)
		wall_color = shade_color(wall_color, 0.70f);
	draw_vertical(core, x, 0, draw_start - 1, ceil_color);
	draw_vertical_texture(core, x, draw_start, draw_end);
	draw_vertical(core, x, draw_end + 1, HEIGHT - 1, floor_color);
}

void	draw_3d(t_core *core)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(core, x);
		set_step(core);
		dda(core);
		calc_perp_wall_dist(core);
		draw_to_screen(core, x);
		x++;
	}
}
