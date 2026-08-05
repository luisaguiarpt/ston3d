/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 13:01:06 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 13:01:07 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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

void	draw_spr_stripe(t_core *core, t_spr_data *s, int stripe)
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
