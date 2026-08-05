/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_gate_overlay.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:53:56 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 11:53:57 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_gate_column(t_core *core, int x)
{
	double	wall_x;
	int		tex_x;

	if (!dda_to_gate(core))
		return ;
	calc_perp_wall_dist(core);
	if (core->ray.perp_wall_dist >= core->zbuffer[x])
		return ;
	if (core->ray.side == 0)
		wall_x = core->player.y + core->ray.perp_wall_dist
			* core->ray.ray_dir_y;
	else
		wall_x = core->player.x + core->ray.perp_wall_dist
			* core->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * core->sprites.gate_img.width)
		- (int)(core->gate.progress * core->sprites.gate_img.width);
	if (tex_x < 0 || tex_x >= core->sprites.gate_img.width)
		return ;
	core->ray.tex = &core->sprites.gate_img;
	calc_wall_slice(core);
	core->ray.tex_x = tex_x;
	get_draw_info(core);
	draw_gate_pixels(core, x, tex_x);
}

void	draw_gate_overlay(t_core *core)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(core, x);
		set_step(core);
		draw_gate_column(core, x);
		x++;
	}
}
