/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:33:25 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 10:33:34 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	init_arms(t_core *core)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		core->sprites.left_arm[i].img = NULL;
		core->sprites.left_arm[i].addr = NULL;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		core->sprites.right_arm[i].img = NULL;
		core->sprites.right_arm[i].addr = NULL;
		i++;
	}
	core->sprites.curr_left = 0;
	core->sprites.curr_right = 0;
}

static void	init_collectibles(t_core *core)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		core->sprites.collectibles[i].img = NULL;
		core->sprites.collectibles[i].addr = NULL;
		i++;
	}
}

static void	init_smoke(t_core *core)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		core->sprites.smoke[i].img = NULL;
		core->sprites.smoke[i].addr = NULL;
		i++;
	}
	core->sprites.smoke_frame = 0;
	core->sprites.smoke_playing = false;
}

void	init_sprites(t_core *core)
{
	init_arms(core);
	init_collectibles(core);
	init_smoke(core);
	core->sprites.end_card.img = NULL;
	core->sprites.end_card.addr = NULL;

}

void	init_textures(t_core *core)
{
	core->textures.no_path = NULL;
	core->textures.so_path = NULL;
	core->textures.ea_path = NULL;
	core->textures.we_path = NULL;
	core->textures.no_img.img = NULL;
	core->textures.so_img.img = NULL;
	core->textures.ea_img.img = NULL;
	core->textures.we_img.img = NULL;
	core->textures.no_img.addr = NULL;
	core->textures.so_img.addr = NULL;
	core->textures.ea_img.addr = NULL;
	core->textures.we_img.addr = NULL;
	core->textures.f_loaded = false;
	core->textures.c_loaded = false;
}
