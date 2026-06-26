/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 18:15:00 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:17:14 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	add_collectible(t_core *core, int x, int y, int type)
{
	int	n;

	if (core->num_collectibles >= 3)
		error_parsing(core, ERR_TOO_MANY_COLL, 0);
	n = core->num_collectibles;
	core->collectibles[n].x = (float)x + 0.5f;
	core->collectibles[n].y = (float)y + 0.5f;
	core->collectibles[n].type = type;
	core->collectibles[n].collected = false;
	core->collectibles[n].dist = 0.0;
	core->num_collectibles++;
	core->map.grid[y][x] = '0';
}

void	find_collectibles(t_core *core)
{
	int	y;
	int	x;
	int	type;

	core->num_collectibles = 0;
	core->collectibles = ft_calloc(3, sizeof(t_collectible));
	if (!core->collectibles)
		error_parsing(core, ERR_MEMORY, 0);
	y = 0;
	while (core->map.grid[y])
	{
		x = 0;
		while (core->map.grid[y][x])
		{
			type = bonus_char_type(core->map.grid[y][x]);
			if (type >= 0)
				add_collectible(core, x, y, type);
			x++;
		}
		y++;
	}
	if (core->num_collectibles != 3)
		error_parsing(core, ERR_COLL_NUM, 0);
}
