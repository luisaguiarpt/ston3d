/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:39:29 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/16 17:08:54 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static char	*store_texture(t_core *core, int map_fd, char *line, int i)
{
	int		j;
	int		len;
	char	*file;

	if (!is_xpm_file(line))
		error_parsing(core, ERR_FORMAT, map_fd);
	while (is_space(line[i]))
		i++;
	j = 0;
	len = ft_strlen(line);
	file = malloc((len - i + 1) * sizeof(char));
	if (!file)
		error_parsing(core, ERR_MEMORY, map_fd);
	while (line[i])
	{
		file[j] = line[i];
		j++;
		i++;
	}
	file[j] = '\0';
	return (file);
}

static void	load_colour(t_core *core, int map_fd, char *line, int i)
{
	int	*array;
	int	values_loaded;
	int	num;

	if (line[i++] == 'F')
		array = core->textures.floor;
	else
		array = core->textures.ceiling;
	values_loaded = 0;
	while(line[i])
	{
		if (values_loaded > 0 && values_loaded < 3)
		{
			if (line[i++] != ',')
				error_parsing(core, ERR_COMMA, map_fd);
		}
		while (is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		if (!ft_isdigit(line[i]))
			error_parsing(core, ERR_COLOR_FORMAT, map_fd);
		num = 0;
		while (ft_isdigit(line[i]))
			num = num * 10 + (line[i++] - '0');
		if (num < 0 || num > 255)
			error_parsing(core, ERR_COLOR_VALUE, map_fd);
		array[values_loaded++] = num;
	}
	if (values_loaded != 3)
		error_parsing(core, ERR_COLOR_COUNT, map_fd);
}

static bool	find_textures(t_core *core, int map_fd, char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	// TODO - starts_with function for readability
	if (line[i] == 'N' && line[i + 1] == 'O' && !core->textures.no_path)
		core->textures.no_path = store_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O' && !core->textures.so_path)
		core->textures.so_path = store_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && !core->textures.we_path)
		core->textures.we_path = store_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && !core->textures.ea_path)
		core->textures.ea_path = store_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'F') // TODO think of the best way to verify there are nor F and C duplicates
		load_colour(core, map_fd, line, i);
	else if (line[i] == 'C')
		load_colour(core, map_fd, line, i);
	else
		return (false);
	return (true);
}

void	parse_textures(t_core *core, int map_fd)
{
	int		textures_stored;
	char	*line;

	textures_stored = 0;
	while (textures_stored < 6)
	{
		line = get_next_line(map_fd);
		if (!line)
			error_parsing(core, ERR_READ, map_fd);
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (!find_textures(core, map_fd, line))
		{
			free(line);
			error_parsing(core, ERR_TEXTURE, map_fd);
		}
		free(line);
		textures_stored++;
	}
}
