/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_markers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 12:48:28 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 12:48:29 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_rect(t_core *core, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < core->minimap.tile_size)
	{
		x = 0;
		while (x < core->minimap.tile_size)
		{
			if (start_x + x >= 0 && start_x + x < WIDTH
				&& start_y + y >= 0 && start_y + y < HEIGHT)
				put_pixel(core, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_collectible_dots(t_core *core)
{
	int	i;
	int	dot_x;
	int	dot_y;

	if (!core->collectibles)
		return ;
	i = 0;
	while (i < core->num_collectibles)
	{
		if (!core->collectibles[i].collected)
		{
			dot_x = core->minimap.offset_x
				+ (int)(core->collectibles[i].x * core->minimap.tile_size);
			dot_y = core->minimap.offset_y
				+ (int)(core->collectibles[i].y * core->minimap.tile_size);
			draw_rect(core, dot_x - 4, dot_y - 4, 0x00FFFF00);
		}
		i++;
	}
}

void	draw_player_dot(t_core *core)
{
	int	x;
	int	y;

	x = core->minimap.offset_x
		+ (int)((core->player.x) * core->minimap.tile_size);
	y = core->minimap.offset_y
		+ (int)((core->player.y) * core->minimap.tile_size);
	draw_rect(core, x - 4, y - 4, 0x00FF0000);
}

void	draw_dir_line(t_core *core)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;
	int		i;

	x = core->minimap.offset_x + (core->player.x) * core->minimap.tile_size;
	y = core->minimap.offset_y + (core->player.y) * core->minimap.tile_size;
	step_x = core->player.dir_x;
	step_y = core->player.dir_y;

	i = 0;
	while (i < 10)
	{
		if ((int)x >= 0 && (int)x < WIDTH && (int)y >= 0 && (int)y < HEIGHT)
			put_pixel(core, (int)x, (int)y, 0xFFFF8F);
		x += step_x;
		y += step_y;
		i++;
	}
}
