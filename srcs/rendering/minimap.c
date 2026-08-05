/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:13 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:40:27 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	cell_color(char c)
{
	if (c == '1')
		return (0x00FFFFFF);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x00333333);
	if (c == 'G')
		return (0x003399FF);
	return (-1);
}

static void	draw_cell(t_core *core, int x, int y)
{
	int		rowlen;
	int		color;
	char	cell;

	rowlen = (int)ft_strlen(core->map.grid[y]);
	if (x < rowlen)
		cell = core->map.grid[y][x];
	else 
		cell = '1';
	color = cell_color(cell);
	if (color == -1)
		return ;
	draw_rect(core,
			core->minimap.offset_x + x * core->minimap.tile_size, 
			core->minimap.offset_y + y * core->minimap.tile_size,
			color);
}

static void	draw_tiles(t_core *core)
{
	int	x;
	int	y;

	y = 0;
	while (y < core->map.height && core->map.grid[y])
	{
		x = 0;
		while (x < core->map.width)
			draw_cell(core, x++, y);
		y++;
	}
}

void	draw_minimap(t_core *core)
{
	draw_tiles(core);
	draw_collectible_dots(core);
	draw_player_dot(core);
	draw_dir_line(core);
}
