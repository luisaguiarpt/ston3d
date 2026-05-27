#include "../../incs/cub3d.h"

char	*load_texture(char *line, int i)
{
	int		j;
	int		len;
	char	*file;

	if (!is_xpm_file(line))
		exit(EXIT_FAILURE);
	while (is_space(line[i]))
		i++;
	j = 0;
	len = ft_strlen(line);
	file = malloc((len - i) * sizeof(char));
	while (line[i])
	{
		file[j] = line[i];
		j++;
		i++;
	}
	return (file);
}

bool	find_textures(t_core *core, char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		core->textures->north = load_texture(line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		core->textures->south = load_texture(line, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		core->textures->west = load_texture(line, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		core->textures->east = load_texture(line, i + 2);
	// else if (line[i] == 'F')
	// 	core->textures->floor = load_texture(line, i + 2);
	// else if (line[i] == 'C')
	// 	core->textures->ceiling = load_texture(line, i + 2);
	else
		return (false);
	return (true);
}

void	parse_map_file(t_core *core, char *map_path)
{
	int		map_fd;
	char	*line;
	int		i;
	
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Error loading map");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 4) // i < 4 just to load the North, South, East and West textures
	{
		line = get_next_line(map_fd);
		line = ft_strtrim(line, "\n"); // to remove the \n at the end of the line
		find_textures(core, line);
		free(line);
		i++;
	}
}
