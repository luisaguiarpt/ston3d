/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:06 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 22:18:16 by josepedr         ###   ########.fr       */
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

void	setup_keybinds(t_core *core)
{
	if (BONUS)
	{
		mlx_hook(core->win, 6, 1L << 6, (int (*)())(void *)handle_mouse, core);
		mlx_mouse_hide(core->mlx, core->win); // TODO mlx function has leaks, evaluate how to deal with this
	}
	mlx_hook(core->win, 2, 1L << 0, (int (*)())(void *)handle_input_press, core);
	mlx_hook(core->win, 3, 1L << 1, (int (*)())(void *)handle_input_release, core);
	mlx_hook(core->win, 17, 1 << 0, (int (*)())(void *)exit_game, core);
}
int	handle_input_press(int key, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (key == XK_Escape)
		exit_game(core, EXIT_SUCCESS);
	else if (key == XK_Left)
		core->input.left = true;
	else if (key == XK_Right)
		core->input.right = true;
	else if (key == XK_w)
		core->input.w = true;
	else if (key == XK_a)
		core->input.a = true;
	else if (key == XK_s)
		core->input.s = true;
	else if (key == XK_d)
		core->input.d = true;
	return (0);
}

int	handle_input_release(int key, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (key == XK_Left)
		core->input.left = false;
	else if (key == XK_Right)
		core->input.right = false;
	else if (key == XK_w)
		core->input.w = false;
	else if (key == XK_a)
		core->input.a = false;
	else if (key == XK_s)
		core->input.s = false;
	else if (key == XK_d)
		core->input.d = false;
	return (0);
}
