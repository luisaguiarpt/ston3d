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
					error_parsing(core, "map can't have more than one player spawn point", -1);
				core->player.x = x;
				core->player.y = y;
				core->player.dir = core->map.grid[y][x];
				player_found = true;
			}
			x++;
		}
		y++;
	}
	if (!player_found)
		error_parsing(core, "map must contain one player spawn point", -1);
}

static void	free_map_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

static void	append_map_line(t_core *core, int map_fd, t_list **lines, char *line)
{
	t_list	*node;
	char	*dup;

	if (!is_valid_line(line))
	{
		free_map_list(*lines);
		free(line);
		error_parsing(core,
			"only the characters 0, 1, N, S, E and W are valid for the map",
			map_fd);
	}
	dup = ft_strdup(line);
	if (!dup)
	{
		free_map_list(*lines);
		free(line);
		error_parsing(core, "not enough memory", map_fd);
	}
	node = ft_lstnew(dup);
	if (!node)
	{
		free_map_list(*lines);
		free(dup);
		free(line);
		error_parsing(core, "not enough memory", map_fd);
	}
	ft_lstadd_back(lines, node);
	free(line);
}

static void	map_list_to_grid(t_core *core, int map_fd, t_list *lines, int height)
{
	t_list	*tmp;
	t_list	*next;
	int		i;

	core->map.grid = ft_calloc(height + 1, sizeof(char *));
	if (!core->map.grid)
	{
		free_map_list(lines);
		error_parsing(core, "not enough memory", map_fd);
	}
	i = 0;
	tmp = lines;
	while (tmp)
	{
		core->map.grid[i++] = tmp->content;
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	parse_map(t_core *core, int map_fd, t_parse_ctx *ctx)
{
	t_list	*lines;
	char	*line;
	int		height;
	bool	found_empty;

	lines = NULL;
	height = 0;
	found_empty = false;
	line = ft_strdup(ctx->first_map_line);
	if (!line)
		error_parsing(core, "not enough memory", map_fd);
	append_map_line(core, map_fd, &lines, line);
	height++;
	while ((line = get_next_line(map_fd)))
	{
		ctx->line_no++;
		remove_newline(line);
		if (is_empty_line(line))
		{
			found_empty = true;
			free(line);
			continue ;
		}
		if (found_empty)
		{
			free_map_list(lines);
			free(line);
			error_parsing(core, "map cannot contain empty lines between rows", map_fd);
		}
		append_map_line(core, map_fd, &lines, line);
		height++;
	}
	core->map.height = height;
	map_list_to_grid(core, map_fd, lines, height);
	get_player_position(core);
	get_map_width(core);
}
