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

static bool	is_wall_at(t_core *core, int x, int y)
{
	if (x < 0 || y < 0 || y >= core->map.height
		|| x >= (int)ft_strlen(core->map.grid[y]))
		return (false);
	return (core->map.grid[y][x] == '1');
}

static char	*check_gate(t_core *core, char **visited)
{
	int	x;
	int	y;

	x = core->gate.x;
	y = core->gate.y;
	if (visited[y][x] != 'F')
		return (ERR_GATE_UNREACHABLE);
	if ((is_wall_at(core, x - 1, y) && is_wall_at(core, x + 1, y))
		|| (is_wall_at(core, x, y - 1) && is_wall_at(core, x, y + 1)))
		return (NULL);
	return (ERR_GATE_PLACEMENT);
}

int	validate_map(t_core *core)
{
	char	**visited;
	char	*err;

	visited = copy_map(core->map.grid, core->map.height);
	if (!visited)
		error_parsing(core, ERR_MEMORY, 0);
	err = NULL;
	if (flood_fill((int)core->player.y, (int)core->player.x, visited, core))
		err = ERR_WALLS;
	else if (BONUS)
		err = check_gate(core, visited);
	ft_free_tab(visited);
	if (err)
		error_parsing(core, err, 0);
	return (0);
}
