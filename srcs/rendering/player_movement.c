/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 12:55:53 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 12:55:55 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	move_forward(t_core *core)
{
	float	new_x;
	float	new_y;

	if (is_walking(core))
	{
		new_x = core->player.x + core->player.dir_x * SPEED;
		new_y = core->player.y + core->player.dir_y * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}

void	move_backward(t_core *core)
{
	float	new_x;
	float	new_y;

	if (is_walking(core))
	{
		new_x = core->player.x - core->player.dir_x * SPEED;
		new_y = core->player.y - core->player.dir_y * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}

void	strafe_left(t_core *core)
{
	float	new_x;
	float	new_y;

	if (is_walking(core))
	{
		new_x = core->player.x + core->player.dir_y * SPEED;
		new_y = core->player.y - core->player.dir_x * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}

void	strafe_right(t_core *core)
{
	float	new_x;
	float	new_y;

	if (is_walking(core))
	{
		new_x = core->player.x - core->player.dir_y * SPEED;
		new_y = core->player.y + core->player.dir_x * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}
