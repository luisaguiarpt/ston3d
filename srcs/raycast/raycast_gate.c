/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_gate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:53:46 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 11:53:47 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	is_wall_no_gate(t_core *core, int map_x, int map_y)
{
	char	cell;

	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
	if ((int)ft_strlen(core->map.grid[map_y]) <= map_x)
		return (1);
	cell = core->map.grid[map_y][map_x];
	return (cell == '1');
}

static int	is_gate_cell(t_core *core, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_y >= core->map.height)
		return (0);
	if ((int)ft_strlen(core->map.grid[map_y]) <= map_x)
		return (0);
	return (core->map.grid[map_y][map_x] == 'G');
}

void	dda_skip_gate(t_core *core)
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
		if (is_wall_no_gate(core, core->ray.map_x, core->ray.map_y))
			hit = 1;
	}
}

int	dda_to_gate(t_core *core)
{
	core->ray.side = 0;
	while (1)
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
		if (is_gate_cell(core, core->ray.map_x, core->ray.map_y))
			return (1);
		if (is_wall(core, core->ray.map_x, core->ray.map_y))
			return (0);
	}
}

void	draw_gate_pixels(t_core *core, int x, int tex_x)
{
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	tex_pos = (core->ray.draw_start - core->ray.true_draw_start)
		* core->ray.draw_step;
	y = core->ray.draw_start;
	while (y <= core->ray.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= core->ray.tex->height)
			tex_y = core->ray.tex->height - 1;
		color = get_pixel_from_texture(core->ray.tex, tex_x, tex_y);
		if (color != (int)SPRITES_BG_COLOR)
			put_pixel(core, x, y, color);
		tex_pos += core->ray.draw_step;
		y++;
	}
}
