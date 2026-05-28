#include "../../incs/cub3d.h"

static void	skip_textures(int fd)
{
	int		textures_skipped;
	char	*line;

	textures_skipped = 0;
	while (textures_skipped < 6) // TODO change it to handle floor and ceiling colors
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

static int	get_map_height(char *map_path)
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

static char	*fill_map_grid(t_core *core, int map_fd, char *line)
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
