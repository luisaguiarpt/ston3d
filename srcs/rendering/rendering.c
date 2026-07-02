/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/07/02 15:40:38 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_end_card(t_core *core)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	start_x = (WIDTH - core->sprites.end_card.width) / 2;
	start_y = ((HEIGHT - core->sprites.end_card.height) / 2) - 150;
	y = 0;
	while (y < core->sprites.end_card.height)
	{
		x = 0;
		while (x < core->sprites.end_card.width)
		{
			color = get_pixel_from_texture(&core->sprites.end_card,
					x, y);
			if (color != SPRITES_BG_COLOR)
				put_pixel(core, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	trigger_end_card(t_core *core)
{
	int	target_time;

	target_time = core->end_time + 3000; // 3 second delay
	if (get_current_time() >= target_time)
		draw_end_card(core);
}

void	put_pixel(t_core *core, int x, int y, int color)
{
    unsigned int	*dst;

    dst = (unsigned int *)(core->img_addr
            + (y * core->line_len)
            + x * core->bpp_bytes);
    *dst = color;
}

int	render_frame(t_core *core)
{
	//core->anim_tick++;
	draw_3d(core);
	if (BONUS)
	{
		render_collectibles(core);
		draw_minimap(core);
		draw_arms(core);
		if (core->game_ended)
		{
			if (core->click_count > 0)
				apply_shutter_effect(core);
			smoke_animation(core);
			trigger_end_card(core);
		}
	}
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	return (0);
}

// TODO - debug only
void	clear_image(t_core *core, int color)
{
	int				y;
	int				x;
//	int				bytespp;
	unsigned int	*row;

	if (!core || !core->img_addr)
		return ;

//	bytespp = core->bpp / 8;
	y = 0;
	while (y < HEIGHT)
	{
		row = (unsigned int *)(core->img_addr + y * core->line_len);
		x = 0;
		while (x < WIDTH)
			row[x++] = (unsigned int)color;
		y++;
	}
}
