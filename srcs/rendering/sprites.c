/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:23:47 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	calc_spr_screen(t_spr_data *s)
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
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	else
		s->draw_start_x = s->raw_start_x;
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

void	draw_spr(t_core *core, t_spr_data *s)
{
	int	stripe;

	stripe = s->draw_start_x;
	while (stripe <= s->draw_end_x)
	{
		draw_spr_stripe(core, s, stripe);
		stripe++;
	}
}
