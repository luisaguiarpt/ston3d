/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 18:04:10 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:05:22 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	set_planes(t_core *core, char dir)
{
	if (dir == 'N')
	{
		core->player.plane_x = FOV;
		core->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		core->player.plane_x = -FOV;
		core->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		core->player.plane_x = 0;
		core->player.plane_y = FOV;
	}
	else if (dir == 'W')
	{
		core->player.plane_x = 0;
		core->player.plane_y = -FOV;
	}
}

static void	set_player_direction(t_core *core, char dir)
{
	if (dir == 'N')
	{
		core->player.dir_x = 0;
		core->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		core->player.dir_x = 0;
		core->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		core->player.dir_x = 1;
		core->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		core->player.dir_x = -1;
		core->player.dir_y = 0;
	}
	set_planes(core, dir);
}

void	get_player_position(t_core *core)
{
	int		x;
	int		y;
	bool	player_found;

	y = 0;
	player_found = false;
	while (core->map.grid[y])
	{
		x = 0;
		while (core->map.grid[y][x])
		{
			if (core->map.grid[y][x] == 'N'
				|| core->map.grid[y][x] == 'S'
				|| core->map.grid[y][x] == 'E'
				|| core->map.grid[y][x] == 'W')
			{
				if (player_found)
					error_parsing(core, ERR_TOO_MANY_PLAYERS, 0);
				core->player.x = x + 0.5f;
				core->player.y = y + 0.5f;
				set_player_direction(core, core->map.grid[y][x]);
				player_found = true;
			}
			x++;
		}
		y++;
	}
	if (!player_found)
		error_parsing(core, ERR_NO_PLAYER, 0);
}
