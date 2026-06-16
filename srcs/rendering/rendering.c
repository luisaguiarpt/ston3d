/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:40:27 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	clear_image(t_core *core, int color);

void	put_pixel(t_core *core, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
		return;
	dst = core->img_addr + (y * core->line_len + x * (core->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_core *core)
{
	//core->anim_tick++;
	clear_image(core, 0x8ace00);
	draw_3d(core);
	if (BONUS)
	{
		render_collectibles(core);
		draw_minimap(core);
		draw_arms(core);
	}
	//draw_player(core); TODO - Render player
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	return (0);
}

// TODO - debug only
void	clear_image(t_core *core, int color)
{
	int				y;
	int				x;
//	int				bytespp;
	unsigned int	*row;

	if (!core || !core->img_addr)
		return ;

//	bytespp = core->bpp / 8;
	y = 0;
	while (y < HEIGHT)
	{
		row = (unsigned int *)(core->img_addr + y * core->line_len);
		x = 0;
		while (x < WIDTH)
			row[x++] = (unsigned int)color;
		y++;
	}
}
