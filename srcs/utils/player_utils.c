/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arms_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 18:26:11 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/26 18:26:21 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	update_arm_sprite(t_core *core)
{
	if (core->game_ended == false)
		core->sprites.curr_right = core->collected_mask & 3;
	core->sprites.curr_left = (core->collected_mask >> 2) & 1;
}

bool	is_walking(t_core *core)
{
	if (core->input.w && core->input.s
		&& !core->input.a && !core->input.d)
		return (false);
	if (core->input.d && core->input.a
		&& !core->input.w && !core->input.s)
		return (false);
	if (core->input.d && core->input.a
		&& core->input.w && core->input.s)
		return (false);
	if (core->input.w || core->input.a
		|| core->input.s || core->input.d)
		return (true);
	return (false);
}
