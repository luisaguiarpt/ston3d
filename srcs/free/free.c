/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:30:53 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 23:37:54 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	exit_game(t_core *core, int exit_code)
{
	free_core(core);
	exit(exit_code);
}

static void	free_map(t_core *core)
{
	if (core->map.grid)
	{
		ft_free_tab(core->map.grid);
		core->map.grid = NULL;
	}
}

static void	free_image(t_core *core, t_img *img)
{
	mlx_destroy_image(core->mlx, img->img);
	// if (img->addr)
	// 	free(img->addr);
}

static void	free_sprites(t_core *core)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (core->sprites.left_arm[i].img)
			free_image(core, &core->sprites.left_arm[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (core->sprites.right_arm[i].img)
			free_image(core, &core->sprites.right_arm[i]);
		if (core->sprites.collectibles[i].img)
			free_image(core, &core->sprites.collectibles[i]);
		i++;
	}
	if (core->sprites.gate_img.img)
		free_image(core, &core->sprites.gate_img);
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
}
