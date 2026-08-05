/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:38:54 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 22:15:33 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	init_map(t_core *core)
{
	core->map.grid = NULL;
	core->map.width = 0;
	core->map.height = 0;
}

static void	init_minimap(t_core *core)
{
	core->minimap.tile_size = 8;
	core->minimap.offset_x = 1000;
	core->minimap.offset_y = 100;
	core->minimap.width = 10;
	core->minimap.height = 10;
}

static void	init_core(t_core *core)
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
	core->num_collectibles = 0;
	core->collected_mask = 0;
	core->collected_count = 0;
	core->collectibles = NULL;
	core->click_count = 0;
	core->prev_frame = ft_calloc(WIDTH * HEIGHT, sizeof(unsigned int));
	if (!core->prev_frame)
		error_parsing(core, ERR_MEMORY, 0);
}

void	init_game(t_core *core)
{
	init_core(core);
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
