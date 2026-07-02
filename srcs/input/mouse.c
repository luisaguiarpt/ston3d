/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 18:02:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:02:21 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	rotate_by_angle(t_core *core, float angle) // mouse_function
{
	float	cos_a;
	float	sin_a;
	float	old_dir_x;
	float	old_plane_x;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	old_dir_x = core->player.dir_x;
	core->player.dir_x = core->player.dir_x * cos_a - core->player.dir_y * sin_a;
	core->player.dir_y = old_dir_x * sin_a + core->player.dir_y * cos_a;
	old_plane_x = core->player.plane_x;
	core->player.plane_x = core->player.plane_x * cos_a - core->player.plane_y * sin_a;
	core->player.plane_y = old_plane_x * sin_a + core->player.plane_y * cos_a;
}

int	handle_mouse(int x, int y, void *param)
{
	t_core	*core;
	int		delta_x;

	(void)y;
	core = (t_core *)param;
	delta_x = x - WIDTH / 2;
	if (delta_x == 0)
		return (0);
	rotate_by_angle(core, delta_x * MOUSE_SENSITIVITY);
	mlx_mouse_move(core->mlx, core->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	handle_click(int button, int x, int y, void *param)
{
	t_core *core;

	core = (t_core *)param;
	(void)x;
	(void)y;
	if (button == 1 && core->game_ended)
	{
		if (core->click_count < SHUTTER_EFFECT_MAX_CLICKS)
			core->click_count++;
		core->input.click = true;
	}
	return (0);
}
