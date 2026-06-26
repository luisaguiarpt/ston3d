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

	if (core->input.w
		|| core->input.a
		|| core->input.s
		|| core->input.d)
		offset += ARM_BOB_SPEED;
	return ((int)(sinf(offset) * ARM_BOB_RANGE));
}

static void	draw_arm_row(t_core *c, t_img *img, int sx, int sy, int y)
{
	unsigned int	*src;
	int				color;
	int				x;

	if (sy + y < 0 || sy + y >= HEIGHT)
		return ;
	src = (unsigned int *)(img->addr + y * img->line_len);
	x = 0;
	while (x < img->width)
	{
		if (sx + x >= 0 && sx + x < WIDTH)
		{
			color = (int)src[x];
			if (color != SPRITES_BG_COLOR)
				put_pixel(c, sx + x, sy + y, color);
		}
		x++;
	}
}

static void	draw_left_arm(t_core *core, int offset, int current)
{
	t_img	*img;
	int		start_x;
	int		start_y;
	int		y;

	img = &core->sprites.left_arm[current];
	start_x = (WIDTH / 2) - 600;
	start_y = HEIGHT - 360 + offset;
	y = 0;
	while (y < img->height)
	{
		draw_arm_row(core, img, start_x, start_y, y);
		y++;
	}
}

static void	draw_right_arm(t_core *core, int offset, int current)
{
	t_img	*img;
	int		start_x;
	int		start_y;
	int		y;

	img = &core->sprites.right_arm[current];
	start_x = (WIDTH / 2);
	start_y = HEIGHT - 320 - offset;
	// adjustment for right_arm sprite number 4
	if (current == 4)
		start_y -= 50;
	y = 0;
	while (y < img->height)
	{
		draw_arm_row(core, img, start_x, start_y, y);
		y++;
	}
}

void	draw_arms(t_core *core)
{
	int	offset;

	offset = calculate_animation_offset(core);
	draw_left_arm(core, offset, core->sprites.curr_left);
	draw_right_arm(core, offset, core->sprites.curr_right);
}
