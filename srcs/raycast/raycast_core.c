/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:53:30 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 11:53:32 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	is_wall(t_core *core, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
	if ((int)ft_strlen(core->map.grid[map_y]) <= map_x)
		return (1);
	if (BONUS && core->map.grid[map_y][map_x] == 'G')
		return (1);
	return (core->map.grid[map_y][map_x] == '1');
}

void	setup_ray(t_core *core, int x)
{
	core->ray.camera_x = 2.0 * x / (double)WIDTH - 1.0;
	core->ray.ray_dir_x = core->player.dir_x
		+ core->player.plane_x * core->ray.camera_x;
	core->ray.ray_dir_y = core->player.dir_y
		+ core->player.plane_y * core->ray.camera_x;
	core->ray.map_x = (int)core->player.x;
	core->ray.map_y = (int)core->player.y;
	if (core->ray.ray_dir_x == 0.0)
		core->ray.delta_dist_x = 1e30;
	else
		core->ray.delta_dist_x = fabs(1.0 / core->ray.ray_dir_x);
	if (core->ray.ray_dir_y == 0.0)
		core->ray.delta_dist_y = 1e30;
	else
		core->ray.delta_dist_y = fabs(1.0 / core->ray.ray_dir_y);
}
//core->ray.delta_dist_x = (core->ray.ray_dir_x == 0.0)
//? 1e30 : fabs(1.0 / core->ray.ray_dir_x);
//core->ray.delta_dist_y = (core->ray.ray_dir_y == 0.0) ?
//1e30 : fabs(1.0 / core->ray.ray_dir_y);

void	set_step(t_core *core)
{
	if (core->ray.ray_dir_x < 0)
	{
		core->ray.step_x = -1;
		core->ray.side_dist_x = (core->player.x - core->ray.map_x)
			* core->ray.delta_dist_x;
	}
	else
	{
		core->ray.step_x = 1;
		core->ray.side_dist_x = (core->ray.map_x + 1.0 - core->player.x)
			* core->ray.delta_dist_x;
	}
	if (core->ray.ray_dir_y < 0)
	{
		core->ray.step_y = -1;
		core->ray.side_dist_y = (core->player.y - core->ray.map_y)
			* core->ray.delta_dist_y;
	}
	else
	{
		core->ray.step_y = 1;
		core->ray.side_dist_y = (core->ray.map_y + 1.0 - core->player.y)
			* core->ray.delta_dist_y;
	}
}

/* core->ray.side:
 * 0 = hit x-side, 1 = hit y-side */
void	dda(t_core *core)
{
	int	hit;

	hit = 0;
	core->ray.side = 0;
	while (!hit)
	{
		if (core->ray.side_dist_x < core->ray.side_dist_y)
		{
			core->ray.side_dist_x += core->ray.delta_dist_x;
			core->ray.map_x += core->ray.step_x;
			core->ray.side = 0;
		}
		else
		{
			core->ray.side_dist_y += core->ray.delta_dist_y;
			core->ray.map_y += core->ray.step_y;
			core->ray.side = 1;
		}
		if (is_wall(core, core->ray.map_x, core->ray.map_y))
			hit = 1;
	}
}

void	calc_perp_wall_dist(t_core *core)
{
	if (core->ray.side == 0)
		core->ray.perp_wall_dist = (core->ray.side_dist_x
				- core->ray.delta_dist_x);
	else
		core->ray.perp_wall_dist = (core->ray.side_dist_y
				- core->ray.delta_dist_y);
	if (core->ray.perp_wall_dist <= 0.1)
		core->ray.perp_wall_dist = 0.1;
}
