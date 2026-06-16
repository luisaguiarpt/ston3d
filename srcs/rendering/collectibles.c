#include "../../incs/cub3d.h"

static void	update_distances(t_core *core)
{
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (i < core->num_collectibles)
	{
		dx = core->collectibles[i].x - core->player.x;
		dy = core->collectibles[i].y - core->player.y;
		core->collectibles[i].dist = dx * dx + dy * dy;
		i++;
	}
}

static void	sort_collectibles(t_core *core)
{
	t_collectible	tmp;
	int				i;
	int				j;

	i = 0;
	while (i < core->num_collectibles - 1)
	{
		j = i + 1;
		while (j < core->num_collectibles)
		{
			if (core->collectibles[i].dist < core->collectibles[j].dist)
			{
				tmp = core->collectibles[i];
				core->collectibles[i] = core->collectibles[j];
				core->collectibles[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	check_one(t_core *core, int i)
{
	double	dx;
	double	dy;
	double	dist_sq;

	if (core->collectibles[i].collected)
		return ;
	dx = core->collectibles[i].x - core->player.x;
	dy = core->collectibles[i].y - core->player.y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq < (double)(COLLECT_RADIUS * COLLECT_RADIUS))
	{
		core->collectibles[i].collected = true;
		core->collected_count++;
	}
}

void	update_collectibles(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->num_collectibles)
	{
		check_one(core, i);
		i++;
	}
}

static void	calc_spr_transform(t_core *core, t_collectible *col,
				t_spr_data *s)
{
	double	sx;
	double	sy;
	double	inv_det;

	sx = col->x - core->player.x;
	sy = col->y - core->player.y;
	inv_det = 1.0 / (core->player.plane_x * core->player.dir_y
			- core->player.dir_x * core->player.plane_y);
	s->transform_x = inv_det
		* (core->player.dir_y * sx - core->player.dir_x * sy);
	s->transform_y = inv_det
		* (-core->player.plane_y * sx + core->player.plane_x * sy);
}

static void	calc_spr_screen(t_spr_data *s)
{
	s->screen_x = (int)((WIDTH / 2) * (1.0 + s->transform_x / s->transform_y));
	s->height = (int)fabs((double)HEIGHT / s->transform_y);
	s->width = s->height;
	s->draw_start_y = -s->height / 2 + HEIGHT / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->height / 2 + HEIGHT / 2;
	if (s->draw_end_y >= HEIGHT)
		s->draw_end_y = HEIGHT - 1;
	s->raw_start_x = -s->width / 2 + s->screen_x;
	s->draw_start_x = (s->raw_start_x < 0) ? 0 : s->raw_start_x;
	s->draw_end_x = s->width / 2 + s->screen_x;
	if (s->draw_end_x >= WIDTH)
		s->draw_end_x = WIDTH - 1;
}

static int	get_spr_tex_y(t_spr_data *s, int y)
{
	int	tex_y;
	int	d;

	d = y * 256 - HEIGHT * 128 + s->height * 128;
	tex_y = d * s->tex->height / s->height / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= s->tex->height)
		tex_y = s->tex->height - 1;
	return (tex_y);
}

static int	get_spr_tex_x(t_spr_data *s, int stripe)
{
	int	tex_x;

	tex_x = (stripe - s->raw_start_x) * s->tex->width / s->width;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= s->tex->width)
		tex_x = s->tex->width - 1;
	return (tex_x);
}

static void	draw_spr_stripe(t_core *core, t_spr_data *s, int stripe)
{
	int	tex_x;
	int	y;
	int	color;

	if (stripe < 0 || stripe >= WIDTH)
		return ;
	if (s->transform_y <= 0 || s->transform_y >= core->zbuffer[stripe])
		return ;
	tex_x = get_spr_tex_x(s, stripe);
	y = s->draw_start_y;
	while (y <= s->draw_end_y)
	{
		color = get_pixel_from_texture(s->tex, tex_x, get_spr_tex_y(s, y));
		if (color != (int)SPRITES_BG_COLOR)
			put_pixel(core, stripe, y, color);
		y++;
	}
}

static void	draw_spr(t_core *core, t_spr_data *s)
{
	int	stripe;

	stripe = s->draw_start_x;
	while (stripe <= s->draw_end_x)
	{
		draw_spr_stripe(core, s, stripe);
		stripe++;
	}
}

static void	render_one(t_core *core, int i)
{
	t_spr_data	s;

	if (core->collectibles[i].collected)
		return ;
	s.tex = &core->sprites.collectibles[core->collectibles[i].type];
	calc_spr_transform(core, &core->collectibles[i], &s);
	if (s.transform_y <= 0.0)
		return ;
	calc_spr_screen(&s);
	draw_spr(core, &s);
}

void	render_collectibles(t_core *core)
{
	int	i;

	if (!core->collectibles)
		return ;
	update_distances(core);
	sort_collectibles(core);
	i = 0;
	while (i < core->num_collectibles)
	{
		render_one(core, i);
		i++;
	}
}

static int	bonus_char_type(char c)
{
	if (c == 'a')
		return (0);
	if (c == 'b')
		return (1);
	if (c == 'c')
		return (2);
	return (-1);
}

static void	add_collectible(t_core *core, int x, int y, int type)
{
	int	n;

	if (core->num_collectibles >= 3)
		error_parsing(core, "too many collectibles in map", 0);
	n = core->num_collectibles;
	core->collectibles[n].x = (float)x + 0.5f;
	core->collectibles[n].y = (float)y + 0.5f;
	core->collectibles[n].type = type;
	core->collectibles[n].collected = false;
	core->collectibles[n].dist = 0.0;
	core->num_collectibles++;
	core->map.grid[y][x] = '0';
}

void	find_collectibles(t_core *core)
{
	int	y;
	int	x;
	int	type;

	core->num_collectibles = 0;
	core->collectibles = ft_calloc(3, sizeof(t_collectible));
	if (!core->collectibles)
		error_parsing(core, "not enough memory", 0);
	y = 0;
	while (core->map.grid[y])
	{
		x = 0;
		while (core->map.grid[y][x])
		{
			type = bonus_char_type(core->map.grid[y][x]);
			if (type >= 0)
				add_collectible(core, x, y, type);
			x++;
		}
		y++;
	}
	if (core->num_collectibles != 3)
		error_parsing(core, "map must have exactly one 'a', one 'b', one 'c'", 0);
}
