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

void	draw_sprites_row(t_core *c, t_img *img, t_row_draw *pos)
{
	unsigned int	*src;
	int				color;
	int				x;

	if (pos->sy + pos->row < 0 || pos->sy + pos->row >= HEIGHT)
		return ;
	src = (unsigned int *)(img->addr + pos->row * img->line_len);
	x = 0;
	while (x < img->width)
	{
		if (pos->sx + x >= 0 && pos->sx + x < WIDTH)
		{
			color = (int)src[x];
			if (color != SPRITES_BG_COLOR)
				put_pixel(c, pos->sx + x, pos->sy + pos->row, color);
		}
		x++;
	}
}

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
