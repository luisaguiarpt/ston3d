/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:40:27 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_left_arm(t_core *core, int offset, int current)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	start_x = (WIDTH / 2) - 600;
	start_y = HEIGHT - 360 + offset;
	y = 0;
	while (y < core->sprites.left_arm[current].height)
	{
		x = 0;
		while (x < core->sprites.left_arm[current].width)
		{
			color = get_pixel_from_texture(&core->sprites.left_arm[current],
					x, y);
			if (color != SPRITES_BG_COLOR)
				put_pixel(core, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_right_arm(t_core *core, int offset, int current)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	start_x = (WIDTH / 2);
	start_y = HEIGHT - 320 - offset;
	y = 0;
	while (y < core->sprites.right_arm[current].height)
	{
		x = 0;
		while (x < core->sprites.right_arm[current].width)
		{
			color = get_pixel_from_texture(&core->sprites.right_arm[current],
					x, y);
			if (color != SPRITES_BG_COLOR)
				put_pixel(core, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

int	calculate_animation_offset(t_core *core)
{
	static float	offset;

	if (core->input.w
		|| core->input.a
		|| core->input.s
		|| core->input.d)
		offset += ARM_BOB_SPEED;
	return ((int)(sinf(offset) * ARM_BOB_RANGE));
}

void	draw_arms(t_core *core)
{
	int	offset;

	offset = calculate_animation_offset(core);
	draw_left_arm(core, offset, core->sprites.curr_left);
	draw_right_arm(core, offset, core->sprites.curr_right);
}
