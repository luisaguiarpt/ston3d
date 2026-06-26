/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:44 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:25:43 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	update_distances(t_core *core)
{
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (i < core->num_collectibles)
	{
		dx = core->collectibles[i].x - core->player.x;
		dy = core->collectibles[i].y - core->player.y;
		core->collectibles[i].dist = dx * dx + dy * dy;
		i++;
	}
}

static void	calc_spr_transform(t_core *core, t_collectible *col, t_spr_data *s)
{
	double	sx;
	double	sy;
	double	inv_det;

	sx = col->x - core->player.x;
	sy = col->y - core->player.y;
	inv_det = 1.0 / (core->player.plane_x * core->player.dir_y
			- core->player.dir_x * core->player.plane_y);
	s->transform_x = inv_det
		* (core->player.dir_y * sx - core->player.dir_x * sy);
	s->transform_y = inv_det
		* (-core->player.plane_y * sx + core->player.plane_x * sy);
}

static void	render_one(t_core *core, int i)
{
	t_spr_data	s;

	if (core->collectibles[i].collected)
		return ;
	s.tex = &core->sprites.collectibles[core->collectibles[i].type];
	s.draw_start_x = 0; // initialized here because of valgrind error
	calc_spr_transform(core, &core->collectibles[i], &s);
	if (s.transform_y <= 0.0)
		return ;
	calc_spr_screen(&s);
	draw_spr(core, &s);
}

void	render_collectibles(t_core *core)
{
	int	i;

	if (!core->collectibles)
		return ;
	update_distances(core);
	sort_collectibles(core);
	i = 0;
	while (i < core->num_collectibles)
	{
		render_one(core, i);
		i++;
	}
}
