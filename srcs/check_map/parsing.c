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

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line[i])
		return (true);
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else
			return (false);
	}
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
		if (!line)
			error_parsing(core, "not enough memory", map_fd);
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
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

bool	is_valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i])
			&& line[i] != '0'
	  		&& line[i] != '1'
	  		&& line[i] != 'N'
	  		&& line[i] != 'S'
	  		&& line[i] != 'E'
	  		&& line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

char	*fill_map_grid(t_core *core, int map_fd, char *line)
{
	char	*grid_line;

	if (!is_valid_line(line))
	{
		free(line);
		error_parsing(core, "only the characters 0, 1, N, S, E and W are valid for the map", map_fd);
	}
	grid_line = ft_strdup(line);
	if (!grid_line)
	{
		free(line);
		error_parsing(core, "not enough memory", map_fd);
	}
	return (grid_line);
}

void	skip_textures(int fd)
{
	int		textures_skipped;
	char	*line;

	textures_skipped = 0;
	while (textures_skipped < 4) // TODO change it to handle floor and ceiling colors
	{
		line = get_next_line(fd);
		// TODO add guard if fails
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		free(line);
		textures_skipped++;
	}
}

int	get_map_height(char *map_path)
{
	int		new_fd;
	int		height;
	char	*line;

	new_fd = open(map_path, O_RDONLY);
	// TODO add guard if fails
	skip_textures(new_fd);
	height = 0;
	while ((line = get_next_line(new_fd)) != NULL)
	{
		remove_newline(line);
		if (height == 0 && is_empty_line(line))
		{
			free(line);
			continue ;
		}
		height++;
		free(line);
	}
	close(new_fd);
	return (height);
}

void	parse_map(t_core *core, char *map_path, int map_fd)
{
	char	*line;
	int		i;

	core->map.height = get_map_height(map_path);
	i = 0;
	core->map.grid = malloc((core->map.height + 1) * sizeof(char *));
	if (!core->map.grid)
		error_parsing(core, "not enough memory", map_fd);
	core->map.grid[i] = NULL; // rethink logic
	while((line = get_next_line(map_fd)))
	{
		remove_newline(line);
		if (is_empty_line(line) && !core->map.grid[i]) // rethink logic
		{
			free(line);
			continue ;
		}
		core->map.grid[i] = fill_map_grid(core, map_fd, line);
		free(line);
		i++;
	}
	core->map.grid[i] = NULL;
}

void	parse_cub_file(t_core *core, char *map_path)
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
	parse_map(core, map_path, map_fd);
	print_debug(core);
	close(map_fd);
}
