/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:09 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 21:54:09 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

bool	above_frame_rate(void)
{
	static int	last_frame_time;
	int			current_time;
	int			frame_duration_ms;

	current_time = get_current_time();
	frame_duration_ms = 1000 / FPS_TARGET;
	if (current_time - last_frame_time < frame_duration_ms)
		return (true);
	last_frame_time = current_time;
	return (false);
}

void	rotate_dir(t_core *core, int turn_dir)
{
	float	angle;
	float	cos;
	float	sin;
	float	old_dir_x;
	float	old_plane_x;

	angle = (float)DEGREES_PER_PRESS * (float)M_PI / 180.0f;
	if (turn_dir > 0)
		angle = -angle;
	cos = cosf(angle);
	sin = sinf(angle);
	old_dir_x = core->player.dir_x;
	core->player.dir_x = core->player.dir_x * cos - core->player.dir_y * sin;
	core->player.dir_y = old_dir_x * sin + core->player.dir_y * cos;
	old_plane_x = core->player.plane_x;
	core->player.plane_x = core->player.plane_x * cos - core->player.plane_y * sin;
	core->player.plane_y = old_plane_x * sin + core->player.plane_y * cos;
}

int	game_loop(void *param)
{
	t_core		*core;

	core = (t_core *)param;
	if (above_frame_rate())
		return (0);
	if (core->input.left)
		rotate_dir(core, 1);
	if (core->input.right)
		rotate_dir(core, -1);
	if (core->input.w)
		move_forward(core);
	if (core->input.s)
		move_backward(core);
	if (core->input.a)
		strafe_left(core);
	if (core->input.d)
		strafe_right(core);
	if (BONUS)
	{
		update_collectibles(core);
		update_gate(core);
		update_end_state(core);
	}
	render_frame(core);
	return (0);
}
