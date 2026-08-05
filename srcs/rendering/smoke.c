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

static bool	smoke_ready(t_core *core)
{
	int	now;

	now = get_current_time();
	if (now - core->sprites.smoke_last_tick < SMOKE_FRAME_MS)
		return (false);
	core->sprites.smoke_last_tick = now;
	return (true);
}

static void	trigger_smoke_start(t_core *core)
{
	if (!core->input.click || core->sprites.smoke_playing
		|| !core->game_ended)
		return ;
	core->sprites.smoke_playing = true;
	core->sprites.smoke_frame = 0;
	core->input.click = false;
}

static void	draw_smoke(t_core *core, t_img *img)
{
	t_row_draw	pos;

	pos.sx = (WIDTH / 2) - (img->width / 2);
	pos.sy = HEIGHT - img->height;
	pos.row = 0;
	while (pos.row < img->height)
	{
		draw_sprites_row(core, img, &pos);
		pos.row++;
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
	trigger_smoke_start(core);
	if (!core->sprites.smoke_playing)
		return ;
	draw_smoke(core, &core->sprites.smoke[core->sprites.smoke_frame]);
	if (smoke_ready(core))
		advance_smoke_frame(core);
}
