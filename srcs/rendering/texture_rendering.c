/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:15 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:54:05 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	load_xpm(t_core *core, t_img *img, char *path);

static void	load_arm_sprites(t_core *core)
{
	load_xpm(core, &core->sprites.left_arm[0], "sprites/left_arm0.xpm");
	load_xpm(core, &core->sprites.left_arm[1], "sprites/left_arm1.xpm");
	load_xpm(core, &core->sprites.right_arm[0], "sprites/right_arm0.xpm");
	load_xpm(core, &core->sprites.right_arm[1], "sprites/right_arm1.xpm");
	load_xpm(core, &core->sprites.right_arm[2], "sprites/right_arm2.xpm");
	load_xpm(core, &core->sprites.right_arm[3], "sprites/right_arm3.xpm");
}

static void	load_collectible_sprites(t_core *core)
{
	load_xpm(core, &core->sprites.collectibles[0], "sprites/papers.xpm");
	load_xpm(core, &core->sprites.collectibles[1], "sprites/buds.xpm");
	load_xpm(core, &core->sprites.collectibles[2], "sprites/lighter.xpm");
}

void	load_textures(t_core *core)
{
	if (BONUS)
	{
		load_arm_sprites(core);
		load_collectible_sprites(core);
	}
	load_xpm(core, &core->textures.no_img, core->textures.no_path);
	load_xpm(core, &core->textures.so_img, core->textures.so_path);
	load_xpm(core, &core->textures.ea_img, core->textures.ea_path);
	load_xpm(core, &core->textures.we_img, core->textures.we_path);
	core->textures.floor_int = rgb_to_int(core->textures.floor);
	core->textures.ceiling_int = rgb_to_int(core->textures.ceiling);
}

void	load_xpm(t_core *core, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(core->mlx, path, &img->width, &img->height);
	if (!img->img)
		exit_error(core, ERR_XPM);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		exit_error(core, ERR_DATA_ADDR);
}
