/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutter_effect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 15:33:27 by josepedr          #+#    #+#             */
/*   Updated: 2026/07/02 15:37:06 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static float	get_shutter_alpha(t_core *core)
{
	float	t;

	if (core->click_count == 0)
		return (1.0f);
	t = (float)core->click_count / (float)SHUTTER_EFFECT_MAX_CLICKS;
	return (1.0f - t * (1.0f - SHUTTER_EFFECT_MIN_ALPHA));
}

static unsigned int	lerp_channel(unsigned int prev, unsigned int curr, float a)
{
	return ((unsigned int)((float)prev + ((float)curr - (float)prev) * a));
}

static unsigned int	lerp_color(unsigned int prev, unsigned int curr, float a)
{
	return (
		(lerp_channel((prev >> 16) & 0xFF, (curr >> 16) & 0xFF, a) << 16)
		| (lerp_channel((prev >> 8) & 0xFF, (curr >> 8) & 0xFF, a) << 8)
		| lerp_channel(prev & 0xFF, curr & 0xFF, a));
}

void	apply_shutter_effect(t_core *core)
{
	float			alpha;
	unsigned int	*row;
	unsigned int	blended;
	int				x;
	int				y;

	alpha = get_shutter_alpha(core);
	y = 0;
	while (y < HEIGHT)
	{
		row = (unsigned int *)(core->img_addr + y * core->line_len);
		x = 0;
		while (x < WIDTH)
		{
			blended = lerp_color(core->prev_frame[y * WIDTH + x], row[x], alpha);
			row[x] = blended;
			core->prev_frame[y * WIDTH + x] = blended;
			x++;
		}
		y++;
	}
}
