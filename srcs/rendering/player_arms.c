/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_arms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 17:15:24 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 17:15:25 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	calculate_animation_offset(t_core *core)
{
	static float	offset;

	if (is_walking(core))
		offset += ARM_BOB_SPEED;
	return ((int)(sinf(offset) * ARM_BOB_RANGE));
}

static void	draw_left_arm(t_core *core, int offset, int current)
{
	t_img		*img;
	t_row_draw	pos;

	img = &core->sprites.left_arm[current];
	pos.sx = (WIDTH / 2) - 600 - (offset / 2);
	pos.sy = HEIGHT - 430 + offset;
	pos.row = 0;
	while (pos.row < img->height)
	{
		draw_sprites_row(core, img, &pos);
		pos.row++;
	}
}

static void	draw_right_arm(t_core *core, int offset, int current)
{
	t_img		*img;
	t_row_draw	pos;

	img = &core->sprites.right_arm[current];
	pos.sx = (WIDTH / 2) - (offset / 2);
	pos.sy = HEIGHT - 320 - offset;
	if (current == 4)
	{
		if (NSFW)
			pos.sy -= 50;
		else
		{
			pos.sx = (WIDTH / 2) - 400 - (offset / 2);
			pos.sy = HEIGHT - 400 + offset;
		}
	}
	pos.row = 0;
	while (pos.row < img->height)
	{
		draw_sprites_row(core, img, &pos);
		pos.row++;
	}
}

void	draw_arms(t_core *core)
{
	int	offset;

	offset = calculate_animation_offset(core);
	if (core->game_ended && !NSFW)
		draw_right_arm(core, offset, 4);
	else
	{
		draw_left_arm(core, offset, core->sprites.curr_left);
		draw_right_arm(core, offset, core->sprites.curr_right);
	}
}
