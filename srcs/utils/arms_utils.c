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
