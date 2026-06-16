/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gate.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 23:30:12 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 23:30:14 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	init_gate(t_core *core)
{
	core->gate.x = -1;
	core->gate.y = -1;
	core->gate.state = GATE_CLOSED;
	core->gate.progress = 0.0f;
	core->sprites.gate_img.img = NULL;
	core->sprites.gate_img.addr = NULL;
}

void	find_gate(t_core *core)
{
	int	y;
	int	x;

	y = 0;
	while (core->map.grid[y])
	{
		x = 0;
		while (core->map.grid[y][x])
		{
			if (core->map.grid[y][x] == 'G')
			{
				if (core->gate.x != -1)
					error_parsing(core, "only one gate allowed in map", 0);
				core->gate.x = x;
				core->gate.y = y;
			}
			x++;
		}
		y++;
	}
	if (core->gate.x == -1)
		error_parsing(core, "bonus map must have a gate 'G'", 0);
}

void	update_gate(t_core *core)
{
	if (core->gate.state == GATE_OPEN)
		return ;
	if (core->gate.state == GATE_CLOSED && core->collected_count == 3)
		core->gate.state = GATE_OPENING;
	if (core->gate.state != GATE_OPENING)
		return ;
	core->gate.progress += GATE_OPEN_SPEED;
	if (core->gate.progress < 1.0f)
		return ;
	core->gate.progress = 1.0f;
	core->gate.state = GATE_OPEN;
	core->map.grid[core->gate.y][core->gate.x] = '0';
}
