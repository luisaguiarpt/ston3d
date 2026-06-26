/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:11:59 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 22:14:32 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	exit_game(t_core *core, int exit_code)
{
	free_core(core);
	exit(exit_code);
}

static int	check_end_trigger(t_core *core)
{
	float	dx;
	float	dy;

	dx = core->player.x - (core->gate.x + 0.5f);
	dy = core->player.y - (core->gate.y + 0.5f);
	return (dx * dx + dy * dy < END_TRIGGER_RADIUS * END_TRIGGER_RADIUS);
}

void	update_end_state(t_core *core)
{
	if (core->game_ended == true)
		return ;
	if (core->gate.state == GATE_OPEN
		&& check_end_trigger(core))
		core->game_ended = true;
	if (core->game_ended == true)
	{
		core->sprites.curr_right = 4;
		core->end_time = get_current_time();
	}
}
