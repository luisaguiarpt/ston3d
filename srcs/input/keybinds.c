/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:06 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:02:28 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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
