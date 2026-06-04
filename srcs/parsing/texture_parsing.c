#include "../../incs/cub3d.h"

static int	skip_spaces(char *line, int i)
{
	while (is_space(line[i]))
		i++;
	return (i);
}

static bool	is_token(char *line, int i, char *token)
{
	int	len;

	len = (int)ft_strlen(token);
	if (ft_strncmp(line + i, token, len) != 0)
		return (false);
	if (line[i + len] && !is_space(line[i + len]))
		return (false);
	return (true);
}

static char	*trim_value(t_core *core, int map_fd, char *line, int i)
{
	int		start;
	int		end;
	char	*value;

	start = skip_spaces(line, i);
	end = (int)ft_strlen(line);
	while (end > start && is_space(line[end - 1]))
		end--;
	if (end <= start)
		error_parsing(core, "missing value after identifier", map_fd);
	value = ft_substr(line, start, end - start);
	if (!value)
		error_parsing(core, "not enough memory", map_fd);
	return (value);
}

static void	validate_texture_file(t_core *core, int map_fd, char *path)
{
	int	fd;

	if (!is_xpm_file(path))
		error_parsing(core, "textures must be .xpm files", map_fd);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_parsing(core, "texture file does not exist or is not readable", map_fd);
	close(fd);
}

static void	load_colour(t_core *core, int map_fd, char *line, int i)
{
	int	*array;
	int	values_loaded;
	int	num;

	if (line[i] == 'F')
		array = core->textures.floor;
	else
		array = core->textures.ceiling;
	if (array[0] != -1)
		error_parsing(core, "duplicate colour identifier", map_fd);
	i = skip_spaces(line, i + 1);
	values_loaded = 0;
	while (values_loaded < 3)
	{
		if (!ft_isdigit(line[i]))
			error_parsing(core, "wrong format, could not load colour", map_fd);
		num = 0;
		while (ft_isdigit(line[i]))
		{
			num = num * 10 + (line[i] - '0');
			i++;
		}
		if (num < 0 || num > 255)
			error_parsing(core, "colour values must be between 0 and 255", map_fd);
		array[values_loaded] = num;
		values_loaded++;
		i = skip_spaces(line, i);
		if (values_loaded < 3)
		{
			if (line[i] != ',')
				error_parsing(core, "comma expected between colour values", map_fd);
			i++;
			i = skip_spaces(line, i);
		}
	}
	i = skip_spaces(line, i);
	if (line[i] != '\0')
		error_parsing(core, "invalid trailing characters in colour definition", map_fd);
}

static bool	find_textures(t_core *core, int map_fd, char *line)
{
	int		i;
	char	*path;

	i = 0;
	i = skip_spaces(line, i);
	if (is_token(line, i, "NO"))
	{
		if (core->textures.no_path)
			error_parsing(core, "duplicate NO identifier", map_fd);
		path = trim_value(core, map_fd, line, i + 2);
		validate_texture_file(core, map_fd, path);
		core->textures.no_path = path;
	}
	else if (is_token(line, i, "SO"))
	{
		if (core->textures.so_path)
			error_parsing(core, "duplicate SO identifier", map_fd);
		path = trim_value(core, map_fd, line, i + 2);
		validate_texture_file(core, map_fd, path);
		core->textures.so_path = path;
	}
	else if (is_token(line, i, "WE"))
	{
		if (core->textures.we_path)
			error_parsing(core, "duplicate WE identifier", map_fd);
		path = trim_value(core, map_fd, line, i + 2);
		validate_texture_file(core, map_fd, path);
		core->textures.we_path = path;
	}
	else if (is_token(line, i, "EA"))
	{
		if (core->textures.ea_path)
			error_parsing(core, "duplicate EA identifier", map_fd);
		path = trim_value(core, map_fd, line, i + 2);
		validate_texture_file(core, map_fd, path);
		core->textures.ea_path = path;
	}
	else if (is_token(line, i, "F"))
		load_colour(core, map_fd, line, i);
	else if (is_token(line, i, "C"))
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
			error_parsing(core, "missing texture or color identifiers", map_fd);
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (!find_textures(core, map_fd, line))
		{
			free(line);
			error_parsing(core, "invalid texture/color identifier", map_fd);
		}
		free(line);
		textures_stored = 0;
		if (core->textures.no_path)
			textures_stored++;
		if (core->textures.so_path)
			textures_stored++;
		if (core->textures.we_path)
			textures_stored++;
		if (core->textures.ea_path)
			textures_stored++;
		if (core->textures.floor[0] != -1)
			textures_stored++;
		if (core->textures.ceiling[0] != -1)
			textures_stored++;
	}
}
