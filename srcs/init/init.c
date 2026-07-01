/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:38:54 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 22:15:33 by josepedr         ###   ########.fr       */
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
}

void	init_map(t_core *core)
{
	core->map.grid = NULL;
	core->map.width = 0; // TODO maybe initialize right away
	core->map.height = 0; // TODO maybe initialize right away
}

void	init_minimap(t_core *core)
{
	core->minimap.tile_size = 8;
	core->minimap.offset_x = 1000;
	core->minimap.offset_y = 100;
	core->minimap.width = 10;
	core->minimap.height = 10;
}

void	init_input(t_core *core)
{
	core->input.w = false;
	core->input.a = false;
	core->input.s = false;
	core->input.d = false;
	core->input.left = false;
	core->input.right = false;
}

void	init_core(t_core *core)
{
	core->game_ended = false;
	core->end_time = 0;
	core->mlx = NULL;
	core->win = NULL;
	core->img = NULL;
	core->img_addr = NULL;
	core->bpp = 0;
	core->endian = 0;
	core->line_len = 0;
	core->anim_tick = 0;
	core->num_collectibles = 0;
	core->collected_mask = 0;
	core->collected_count = 0;
	core->collectibles = NULL;
	init_textures(core);
	init_map(core);
	init_minimap(core);
	init_input(core);
	if (BONUS)
	{
		init_sprites(core);
		init_gate(core);
	}
}

void	init_mlx(t_core *core)
{
	core->mlx = mlx_init();
	if (!core->mlx)
		exit(EXIT_FAILURE);
	core->win = mlx_new_window(core->mlx, WIDTH, HEIGHT, "ston3d");
	if (!core->win)
		exit(EXIT_FAILURE);
	core->img = mlx_new_image(core->mlx, WIDTH, HEIGHT);
	if (!core->img)
		exit(EXIT_FAILURE);
	core->img_addr = mlx_get_data_addr(core->img, &core->bpp, &core->line_len, &core->endian);
	core->bpp_bytes = core->bpp / 8;
}
