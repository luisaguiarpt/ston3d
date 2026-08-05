/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 12:18:36 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 12:18:47 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_3d(t_core *core)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(core, x);
		set_step(core);
		if (BONUS && core->gate.state == GATE_OPENING)
			dda_skip_gate(core);
		else
			dda(core);
		calc_perp_wall_dist(core);
		core->zbuffer[x] = core->ray.perp_wall_dist;
		draw_to_screen(core, x);
		x++;
	}
	if (BONUS && core->gate.state == GATE_OPENING)
		draw_gate_overlay(core);
}
