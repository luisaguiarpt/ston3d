/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoke.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:49:44 by josepedr          #+#    #+#             */
/*   Updated: 2026/07/01 15:55:24 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	init_smoke(t_core *core)
{
	if (!core->input.click || core->sprites.smoke_playing || !core->game_ended)
		return ;
	core->sprites.smoke_playing = true;
	core->sprites.smoke_frame = 0;
	core->input.click = false;
}

static void	draw_smoke(t_core *core, t_img *img)
{
	int	start_x;
	int	start_y;
	int y;

	start_x = (WIDTH / 2) - (img->width / 2);
	start_y = HEIGHT - img->height;
	y = 0;
	while (y < img->height)
	{
		draw_sprites_row(core, img, start_x, start_y, y);
		y++;
	}
}

static void	advance_smoke_frame(t_core *core)
{
	core->sprites.smoke_frame++;
	if (core->sprites.smoke_frame >= 17)
	{
		core->sprites.smoke_frame = 0;
		core->sprites.smoke_playing = false;
	}
}
void	smoke_animation(t_core *core)
{
	init_smoke(core);
	if (!core->sprites.smoke_playing)
		return ;
	draw_smoke(core, &core->sprites.smoke[core->sprites.smoke_frame]);
	advance_smoke_frame(core);
}
