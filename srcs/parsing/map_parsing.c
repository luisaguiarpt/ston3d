#include "../../incs/cub3d.h"

static void	get_map_width(t_core *core)
{
	int	i;
	int	j;

	i = 0;
	while (core->map.grid[i])
	{
		j = 0;
		while (core->map.grid[i][j])
			j++;
		if (j > core->map.width)
			core->map.width = j;
		i++;
	}
}

static void	set_planes(t_core *core, char dir)
{
	if (dir == 'N')
	{
		core->player.plane_x = FOV;
		core->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		core->player.plane_x = -FOV;
		core->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		core->player.plane_x = 0;
		core->player.plane_y = FOV;
	}
	else if (dir == 'W')
	{
		core->player.plane_x = 0;
		core->player.plane_y = -FOV;
	}
	
}

static void	set_player_direction(t_core *core, char dir)
{
	if (dir == 'N')
	{
		core->player.dir_x = 0;
		core->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		core->player.dir_x = 0;
		core->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		core->player.dir_x = 1;
		core->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		core->player.dir_x = -1;
		core->player.dir_y = 0;
	}
	set_planes(core, dir);
}

static void	get_player_position(t_core *core)
{
	int		x;
	int		y;
	bool	player_found;

	y = 0;
	player_found = false;
	while (core->map.grid[y])
	{
		x = 0;
		while (core->map.grid[y][x])
		{
			if (core->map.grid[y][x] == 'N'
				|| core->map.grid[y][x] == 'S'
				|| core->map.grid[y][x] == 'E'
				|| core->map.grid[y][x] == 'W')
			{
				if (player_found)
					error_parsing(core, "map can't have more than one player spawn point", 0); // TODO mabe use another function that doesnt need to close fds
				core->player.x = x;
				core->player.y = y;
				set_player_direction(core, core->map.grid[y][x]);
				player_found = true;
			}
			x++;
		}
		y++;
	}
	if (!player_found)
		error_parsing(core, "No player found", 0);
}

static void	skip_textures(t_core *core, int fd, int old_fd)
{
	int		textures_skipped;
	char	*line;

	textures_skipped = 0;
	while (textures_skipped < 6) // TODO change it to handle floor and ceiling colors
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(old_fd);
			error_parsing(core, "not enough memory", fd);
		}
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

static int	get_map_height(t_core *core, char *map_path, int old_fd)
{
	int		new_fd;
	int		height;
	char	*line;

	new_fd = open(map_path, O_RDONLY);
	if (new_fd < 0)
		error_parsing(core, strerror(errno), old_fd); // TODO verify if strerror is correct in this case
	skip_textures(core, new_fd, old_fd);
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

	core->map.height = get_map_height(core, map_path, map_fd);
	i = 0;
	core->map.grid = ft_calloc(core->map.height + 1, sizeof(char *));
	if (!core->map.grid)
		error_parsing(core, "not enough memory", map_fd);
	while((line = get_next_line(map_fd)))
	{
		remove_newline(line);
		if (is_empty_line(line) && i == 0)
		{
			free(line);
			continue ;
		}
		core->map.grid[i] = fill_map_grid(core, map_fd, line);
		free(line);
		i++;
	}
	get_player_position(core);
	get_map_width(core);
}
