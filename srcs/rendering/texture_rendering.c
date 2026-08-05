/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:15 by josepedr          #+#    #+#             */
/*   Updated: 2026/07/01 14:43:52 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	load_xpm(t_core *core, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(core->mlx, path,
			&img->width, &img->height);
	if (!img->img)
		exit_error(core, ERR_XPM);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		exit_error(core, ERR_DATA_ADDR);
}

static void	load_collectible_sprites(t_core *core)
{
	if (NSFW)
	{
		load_xpm(core, &core->sprites.collectibles[0],
			"sprites/NSFW/papers.xpm");
		load_xpm(core, &core->sprites.collectibles[1],
			"sprites/NSFW/buds.xpm");
		load_xpm(core, &core->sprites.collectibles[2],
			"sprites/NSFW/lighter.xpm");
	}
	else
	{
		load_xpm(core, &core->sprites.collectibles[0],
			"sprites/PG/tomato.xpm");
		load_xpm(core, &core->sprites.collectibles[1],
			"sprites/PG/lettuce.xpm");
		load_xpm(core, &core->sprites.collectibles[2],
			"sprites/PG/baguette.xpm");
	}
}

static void	load_smoke_sprites(t_core *core)
{
	load_xpm(core, &core->sprites.smoke[0], "sprites/smoke/smoke01.xpm");
	load_xpm(core, &core->sprites.smoke[1], "sprites/smoke/smoke02.xpm");
	load_xpm(core, &core->sprites.smoke[2], "sprites/smoke/smoke03.xpm");
	load_xpm(core, &core->sprites.smoke[3], "sprites/smoke/smoke04.xpm");
	load_xpm(core, &core->sprites.smoke[4], "sprites/smoke/smoke05.xpm");
	load_xpm(core, &core->sprites.smoke[5], "sprites/smoke/smoke06.xpm");
	load_xpm(core, &core->sprites.smoke[6], "sprites/smoke/smoke07.xpm");
	load_xpm(core, &core->sprites.smoke[7], "sprites/smoke/smoke08.xpm");
	load_xpm(core, &core->sprites.smoke[8], "sprites/smoke/smoke09.xpm");
	load_xpm(core, &core->sprites.smoke[9], "sprites/smoke/smoke10.xpm");
	load_xpm(core, &core->sprites.smoke[10], "sprites/smoke/smoke11.xpm");
	load_xpm(core, &core->sprites.smoke[11], "sprites/smoke/smoke12.xpm");
	load_xpm(core, &core->sprites.smoke[12], "sprites/smoke/smoke13.xpm");
	load_xpm(core, &core->sprites.smoke[13], "sprites/smoke/smoke14.xpm");
	load_xpm(core, &core->sprites.smoke[14], "sprites/smoke/smoke15.xpm");
	load_xpm(core, &core->sprites.smoke[15], "sprites/smoke/smoke16.xpm");
	load_xpm(core, &core->sprites.smoke[16], "sprites/smoke/smoke17.xpm");
}

void	load_textures(t_core *core)
{
	if (BONUS)
	{
		load_arm_sprites(core);
		load_smoke_sprites(core);
		load_collectible_sprites(core);
		load_xpm(core, &core->sprites.gate_img, "sprites/gate.xpm");
		load_xpm(core, &core->sprites.end_card, "sprites/end_card.xpm");
	}
	load_xpm(core, &core->textures.no_img, core->textures.no_path);
	load_xpm(core, &core->textures.so_img, core->textures.so_path);
	load_xpm(core, &core->textures.ea_img, core->textures.ea_path);
	load_xpm(core, &core->textures.we_img, core->textures.we_path);
	core->textures.floor_int = rgb_to_int(core->textures.floor);
	core->textures.ceiling_int = rgb_to_int(core->textures.ceiling);
}
