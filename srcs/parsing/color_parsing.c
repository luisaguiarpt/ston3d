/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 10:46:16 by josepedr          #+#    #+#             */
/*   Updated: 2026/08/05 10:46:19 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	*select_color_array(t_core *core, char c)
{
	if (c == 'F')
		return (core->textures.floor);
	return (core->textures.ceiling);
}

static int	parse_one_rgb(t_core *core, int map_fd, char *line, int *i)
{
	int	rgb_value;

	while (is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		return (-1);
	if (!ft_isdigit(line[*i]))
	{
		free(line);
		error_parsing(core, ERR_COLOR_FORMAT, map_fd);
	}
	rgb_value = 0;
	while (ft_isdigit(line[*i]))
		rgb_value = rgb_value * 10 + (line[(*i)++] - '0');
	if (rgb_value < 0 || rgb_value > 255)
	{
		free(line);
		error_parsing(core, ERR_COLOR_VALUE, map_fd);
	}
	return (rgb_value);
}

void	load_color(t_core *core, int map_fd, char *line, int i)
{
	int	*array;
	int	values_loaded;
	int	value;

	array = select_color_array(core, line[i++]);
	values_loaded = 0;
	while (values_loaded < 3)
	{
		if (values_loaded > 0 && line[i++] != ',')
			error_parsing(core, ERR_COMMA, map_fd);
		value = parse_one_rgb(core, map_fd, line, &i);
		if (value == -1)
			error_parsing(core, ERR_COLOR_COUNT, map_fd);
		array[values_loaded++] = value;
	}
}
