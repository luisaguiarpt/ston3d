#include "../../incs/cub3d.h"

void	free_textures(t_core *core)
{
	if (core->textures.north)
		free(core->textures.north);
	if (core->textures.south)
		free(core->textures.south);
	if (core->textures.east)
		free(core->textures.east);
	if (core->textures.west)
		free(core->textures.west);
	// TODO free ceiling and floor
}

void	free_core(t_core *core)
{
	if (core->mlx)
		free(core->mlx);
	// TODO check if window also needs to be freed
	free_textures(core);
}

void	error_parsing(t_core *core, char *message, int map_fd)
{
	ft_printf("error: %s\n", message);
	free_core(core);
	close(map_fd);
	exit(EXIT_FAILURE);
}
char	*load_texture(t_core *core, int map_fd, char *line, int i)
{
	int		j;
	int		len;
	char	*file;

	if (!is_xpm_file(line))
		error_parsing(core, "textures must be .xpm files", map_fd);
	while (is_space(line[i]))
		i++;
	j = 0;
	len = ft_strlen(line);
	file = malloc((len - i + 1) * sizeof(char));
	if (!file)
		error_parsing(core, "not enough memory", map_fd);
	while (line[i])
	{
		file[j] = line[i];
		j++;
		i++;
	}
	file[j] = '\0';
	return (file);
}

bool	find_textures(t_core *core, int map_fd, char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		core->textures.north = load_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		core->textures.south = load_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		core->textures.west = load_texture(core, map_fd, line, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		core->textures.east = load_texture(core, map_fd, line, i + 2);
	// else if (line[i] == 'F')
	// 	core->textures->floor = load_texture(core, map_fd, line, i + 2);
	// else if (line[i] == 'C')
	// 	core->textures->ceiling = load_texture(core, map_fd, line, i + 2);
	else
		return (false);
	return (true);
}

void	parse_textures(t_core *core, int map_fd)
{
	int		textures_loaded;
	char	*line;

	textures_loaded = 0;
	while (textures_loaded < 4) // TODO needs to also parse ceiling and floor colors
	{
		line = get_next_line(map_fd);
		remove_newline(line);
		if (!find_textures(core, map_fd, line))
		{
			error_parsing(core, "unable to find textures from the .cub file", map_fd);
			free(line);
		}
		free(line);
		textures_loaded++;
	}
}

void	parse_map_file(t_core *core, char *map_path)
{
	int		map_fd;
	
	if (!is_cub_file(map_path))
	{
		ft_printf("error: map must be a .cub file\n");
		exit(EXIT_FAILURE);
	}
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Error loading map");
		exit(EXIT_FAILURE);
	}
	parse_textures(core, map_fd);
	close(map_fd);
}
