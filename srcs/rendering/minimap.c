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


static void	draw_rect(t_core *core, int start_x, int start_y, int color);
static int	cell_color(char c);
static void	draw_cell(t_core *core, int x, int y);
void	draw_tiles(t_core *core);
void	draw_player_dot(t_core *core);
void	draw_dir_line(t_core *core);

static void	draw_collectible_dots(t_core *core)
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

void	draw_minimap(t_core *core)
{
	draw_tiles(core);
	draw_collectible_dots(core);
	draw_player_dot(core);
	draw_dir_line(core);
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
	while (i < 10) // 10 - line size
	{
		put_pixel(core, (int)x, (int)y, 0xFFFF8F);
		x += step_x;
		y += step_y;
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

void	draw_tiles(t_core *core)
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

static void	draw_rect(t_core *core, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < core->minimap.tile_size)
	{
		x = 0;
		while (x < core->minimap.tile_size)
			put_pixel(core, start_x + x++, start_y + y, color);
		y++;
	}
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
		cell = ' ';
	color = cell_color(cell);
	if (color == -1)
		return ;
	draw_rect(core,
			core->minimap.offset_x + x * core->minimap.tile_size, 
			core->minimap.offset_y + y * core->minimap.tile_size,
			color);
}

static int	cell_color(char c)
{
	if (c == '1')
		return (0x00FFFFFF);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x00333333);
	return (-1);
}

//void	draw_line(t_core *core)
//{
//	int	span[2];
//	int	dir[2];
//	int	err[2];
//
//	// TODO - complete function
//}
