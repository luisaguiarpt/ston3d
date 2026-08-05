/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:53:41 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 11:53:42 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	draw_vertical(t_core *core, int x, t_vline *v)
{
	int	y;

	if (x < 0 || x >= WIDTH)
		return ;
	if (v->y0 < 0)
		v->y0 = 0;
	if (v->y1 >= HEIGHT)
		v->y1 = HEIGHT - 1;
	y = v->y0;
	while (y <= v->y1)
		put_pixel(core, x, y++, v->color);
}

static void	draw_vertical_texture(t_core *core, int x,
		int draw_start, int draw_end)
{
	int		tex_y;
	int		y;
	float	tex_pos;

	if (x < 0 || x >= WIDTH || draw_start > draw_end)
		return ;
	tex_pos = (draw_start - core->ray.true_draw_start) * core->ray.draw_step;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= core->ray.tex->height)
			tex_y = core->ray.tex->height - 1;
		put_pixel(core, x, y, get_tex_pixel(core->ray.tex,
				core->ray.tex_x, tex_y));
		tex_pos += core->ray.draw_step;
		y++;
	}
}

void	get_draw_info(t_core *core)
{
	core->ray.true_draw_start = -core->ray.line_height / 2 + HEIGHT / 2;
	core->ray.draw_step = (double)core->ray.tex->height
		/ (double)(core->ray.line_height);
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

void	draw_to_screen(t_core *core, int x)
{
	t_vline	v;

	calc_wall_slice(core);
	calc_wall_x(core);
	get_texture(core);
	calc_tex_x(core);
	get_draw_info(core);
	v.y0 = 0;
	v.y1 = core->ray.draw_start - 1;
	v.color = core->textures.ceiling_int;
	draw_vertical(core, x, &v);
	draw_vertical_texture(core, x, core->ray.draw_start, core->ray.draw_end);
	v.y0 = core->ray.draw_end + 1;
	v.y1 = HEIGHT - 1;
	v.color = core->textures.floor_int;
	draw_vertical(core, x, &v);
}
