/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:30:53 by josepedr          #+#    #+#             */
/*   Updated: 2026/07/01 14:43:02 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static void	free_map(t_core *core)
{
	if (core->map.grid)
	{
		ft_free_tab(core->map.grid);
		core->map.grid = NULL;
	}
}

static void	free_textures(t_core *core)
{
	if (core->textures.no_path)
		free(core->textures.no_path);
	if (core->textures.so_path)
		free(core->textures.so_path);
	if (core->textures.ea_path)
		free(core->textures.ea_path);
	if (core->textures.we_path)
		free(core->textures.we_path);
	if (core->textures.no_img.img)
		free_image(core, &core->textures.no_img);
	if (core->textures.so_img.img)
		free_image(core, &core->textures.so_img);
	if (core->textures.ea_img.img)
		free_image(core, &core->textures.ea_img);
	if (core->textures.we_img.img)
		free_image(core, &core->textures.we_img);
}

void	free_core(t_core *core)
{
	if (BONUS)
	{
		free_sprites(core);
		if (core->collectibles)
			free(core->collectibles);
	}
	free_textures(core);
	free_map(core);
	if (core->img)
		mlx_destroy_image(core->mlx, core->img);
	if (core->win)
		mlx_destroy_window(core->mlx, core->win);
	if (core->mlx)
	{
		mlx_destroy_display(core->mlx);
		free(core->mlx);
	}
	if (core->prev_frame)
		free(core->prev_frame);
}
