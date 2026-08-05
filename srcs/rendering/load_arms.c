/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_arms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 12:42:50 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 12:42:51 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	load_arms_nsfw(t_core *core)
{
	load_xpm(core, &core->sprites.left_arm[1],
		"sprites/NSFW/nsfw_left_arm1.xpm");
	load_xpm(core, &core->sprites.right_arm[1],
		"sprites/NSFW/nsfw_right_arm1.xpm");
	load_xpm(core, &core->sprites.right_arm[2],
		"sprites/NSFW/nsfw_right_arm2.xpm");
	load_xpm(core, &core->sprites.right_arm[3],
		"sprites/NSFW/nsfw_right_arm3.xpm");
	load_xpm(core, &core->sprites.right_arm[4],
		"sprites/NSFW/nsfw_right_arm4.xpm");
}

static void	load_arms_pg(t_core *core)
{
	load_xpm(core, &core->sprites.left_arm[1],
		"sprites/PG/pg_left_arm1.xpm");
	load_xpm(core, &core->sprites.right_arm[1],
		"sprites/PG/pg_right_arm1.xpm");
	load_xpm(core, &core->sprites.right_arm[2],
		"sprites/PG/pg_right_arm2.xpm");
	load_xpm(core, &core->sprites.right_arm[3],
		"sprites/PG/pg_right_arm3.xpm");
	load_xpm(core, &core->sprites.right_arm[4],
		"sprites/PG/pg_right_arm4.xpm");
}

void	load_arm_sprites(t_core *core)
{
	load_xpm(core, &core->sprites.right_arm[0], "sprites/right_arm0.xpm");
	load_xpm(core, &core->sprites.left_arm[0], "sprites/left_arm0.xpm");
	if (NSFW)
		load_arms_nsfw(core);
	else
		load_arms_pg(core);
}
