/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:26:25 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 10:26:27 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	free_image(t_core *core, t_img *img)
{
	mlx_destroy_image(core->mlx, img->img);
}

static void	free_arms(t_core *core)
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
	while (i < 5)
	{
		if (core->sprites.right_arm[i].img)
			free_image(core, &core->sprites.right_arm[i]);
		i++;
	}
}

static void	free_smoke(t_core *core)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (core->sprites.smoke[i].img)
			free_image(core, &core->sprites.smoke[i]);
		i++;
	}
}

void	free_sprites(t_core *core)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (core->sprites.collectibles[i].img)
			free_image(core, &core->sprites.collectibles[i]);
		i++;
	}
	free_arms(core);
	free_smoke(core);
	if (core->sprites.gate_img.img)
		free_image(core, &core->sprites.gate_img);
	if (core->sprites.end_card.img)
		free_image(core, &core->sprites.end_card);
}
