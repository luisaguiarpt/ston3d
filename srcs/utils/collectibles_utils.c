/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 18:14:18 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:26:26 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	check_one(t_core *core, int i)
{
	double	dx;
	double	dy;
	double	dist_sq;

	if (core->collectibles[i].collected)
		return ;
	dx = core->collectibles[i].x - core->player.x;
	dy = core->collectibles[i].y - core->player.y;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq < (double)(COLLECT_RADIUS * COLLECT_RADIUS))
	{
		core->collectibles[i].collected = true;
		core->collected_count++;
		core->collected_mask |= (1 << core->collectibles[i].type);
	}
}

int	bonus_char_type(char c)
{
	if (c == 'a')
		return (0);
	if (c == 'b')
		return (1);
	if (c == 'c')
		return (2);
	return (-1);
}

void	update_collectibles(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->num_collectibles)
	{
		check_one(core, i);
		i++;
	}
	update_arm_sprite(core);
}

void	sort_collectibles(t_core *core)
{
	t_collectible	tmp;
	int				i;
	int				j;

	i = 0;
	while (i < core->num_collectibles - 1)
	{
		j = i + 1;
		while (j < core->num_collectibles)
		{
			if (core->collectibles[i].dist < core->collectibles[j].dist)
			{
				tmp = core->collectibles[i];
				core->collectibles[i] = core->collectibles[j];
				core->collectibles[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
