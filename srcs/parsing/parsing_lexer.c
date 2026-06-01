#include "../../incs/cub3d.h"

bool	is_header_key(char *key)
{
	if (!ft_strcmp(key, "NO"))
		return (true);
	if (!ft_strcmp(key, "SO"))
		return (true);
	if (!ft_strcmp(key, "WE"))
		return (true);
	if (!ft_strcmp(key, "EA"))
		return (true);
	if (!ft_strcmp(key, "F"))
		return (true);
	if (!ft_strcmp(key, "C"))
		return (true);
	return (false);
}

bool	is_map_start_line(char *line)
{
	int	i;
	int	has_map_char;

	if (!is_valid_line(line))
		return (false);
	i = 0;
	has_map_char = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			has_map_char = 1;
		i++;
	}
	return (has_map_char != 0);
}
