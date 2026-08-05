/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 11:54:04 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 11:54:05 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	get_pixel_from_texture(t_img *img, int tex_x, int tex_y)
{
	char	*pixel;
	int		bpp;

	if (!img || !img->addr || img->width <= 0 || img->height <= 0)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_x >= img->width)
		tex_x = img->width - 1;
	if (tex_y >= img->height)
		tex_y = img->height - 1;
	bpp = img->bpp / 8;
	pixel = img->addr + (tex_y * img->line_len + tex_x * bpp);
	return (*(int *)pixel);
}

void	get_texture(t_core *core)
{
	t_img	*tex;

	if (BONUS && core->map.grid[core->ray.map_y][core->ray.map_x] == 'G')
	{
		core->ray.tex = &core->sprites.gate_img;
		return ;
	}
	if (core->ray.side == 0)
	{
		if (core->ray.ray_dir_x > 0)
			tex = &core->textures.we_img;
		else
			tex = &core->textures.ea_img;
	}
	else
	{
		if (core->ray.ray_dir_y > 0)
			tex = &core->textures.no_img;
		else
			tex = &core->textures.so_img;
	}
	core->ray.tex = tex;
}

void	calc_tex_x(t_core *core)
{
	int	tex_x;
	double	wall_x;
	t_img	*tex;

	wall_x = core->ray.wall_x;
	tex = core->ray.tex;
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if(core->ray.side == 0 && core->ray.ray_dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if(core->ray.side == 1 && core->ray.ray_dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	core->ray.tex_x = tex_x;
}

unsigned int	get_tex_pixel(t_img *tex, int tex_x, int tex_y)
{
	char	*dst;

	dst = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	calc_wall_x(t_core *core)
{
	double	wall_x;
	
	if (core->ray.side == 0)
		wall_x = core->player.y + core->ray.perp_wall_dist * core->ray.ray_dir_y;
	else
		wall_x = core->player.x + core->ray.perp_wall_dist * core->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	core->ray.wall_x = wall_x;
}
