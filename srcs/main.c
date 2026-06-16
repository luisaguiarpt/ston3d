/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:39 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 16:40:42 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	t_core	core;

	if (ac != 2)
	{
		ft_printf("usage: ./cub3d <path_to_map>\n");
		exit(EXIT_FAILURE);
	}
	init_core(&core);
	parse_cub_file(&core, av[1]);
	validate_map(&core);
	init_mlx(&core);
	load_textures(&core);
	setup_keybinds(&core);
	mlx_loop_hook(core.mlx, (int (*)())(void *)game_loop, &core);
	mlx_loop(core.mlx);
	return (0);
}
