/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 12:53:23 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 12:53:25 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	is_solid_cell(t_core *core, float x, float y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
	if (map_x >= (int)ft_strlen(core->map.grid[map_y]))
		return (1);
	cell = core->map.grid[map_y][map_x];
	if (cell == '1')
		return (1);
	if (BONUS && cell == 'G' && core->gate.state != GATE_OPEN)
		return (1);
	return (0);
}

int	collides_x(t_core *core, float new_x)
{
	return (is_solid_cell(core, new_x +
				WALL_PADDING, core->player.y + WALL_PADDING)
		|| is_solid_cell(core, new_x +
			WALL_PADDING, core->player.y - WALL_PADDING)
		|| is_solid_cell(core, new_x -
			WALL_PADDING, core->player.y + WALL_PADDING)
		|| is_solid_cell(core, new_x -
			WALL_PADDING, core->player.y - WALL_PADDING));
}

int	collides_y(t_core *core, float new_y)
{
	return (is_solid_cell(core, core->player.x + WALL_PADDING,
				new_y + WALL_PADDING)
		|| is_solid_cell(core, core->player.x + WALL_PADDING,
			new_y - WALL_PADDING)
		|| is_solid_cell(core, core->player.x - WALL_PADDING,
			new_y + WALL_PADDING)
		|| is_solid_cell(core, core->player.x - WALL_PADDING,
			new_y - WALL_PADDING));
}
