/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:22 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 23:38:13 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	parse_cub_file(t_core *core, char *map_path)
{
	int	map_fd;

	if (!is_cub_file(map_path))
		error_parsing(core, "error: map must be a .cub file", 0);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		error_parsing(core, "error loading map", 0);
	parse_textures(core, map_fd);
	parse_map(core, map_path, map_fd);
	get_player_position(core);
	get_map_width(core);
	if (BONUS)
	{
		find_collectibles(core);
		find_gate(core);
	}
	close(map_fd);
}

void	error_parsing(t_core *core, char *message, int map_fd)
{
	ft_printf("Error\n%s\n", message);
	free_core(core);
	if (map_fd)
		close(map_fd);
	exit(EXIT_FAILURE);
}

void	error_parsing_free(t_core *core, char *message, int map_fd, void *p)
{
	free(p);
	error_parsing(core, message, map_fd);
}
