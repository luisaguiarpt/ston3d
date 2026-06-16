/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:34 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 17:09:47 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	flood_fill(int y, int x, char **grid, t_core *core);

int	validate_map(t_core *core)
{
	char	**validation_map;

	validation_map = copy_map(core->map.grid);
	if (!validation_map)
		error_parsing(core, ERR_MEMORY, 0);
	if (flood_fill((int)core->player.y, (int)core->player.x, validation_map, core))
	{
		ft_free_tab(validation_map);
		error_parsing(core, ERR_WALLS, 0);
	}
	ft_free_tab(validation_map);
	return (0);
}

static int	flood_fill(int y, int x, char **grid, t_core *core)
{
	char	cell;

	if (y < 0 || x < 0)
		return (1);
	if (y >= core->map.height || x >= core->map.width)
		return (1);
	cell = grid[y][x];
	if (cell == ' ' || cell == '\0')
		return (1);
	if (cell == '1')
		return (0);
	if (cell == 'F')
		return (0);
	grid[y][x] = 'F';
	if (flood_fill(y + 1, x, grid, core))
		return (1);
	if (flood_fill(y - 1, x, grid, core))
		return (1);
	if (flood_fill(y, x + 1, grid, core))
		return (1);
	if (flood_fill(y, x - 1, grid, core))
		return (1);
	return (0);
}
