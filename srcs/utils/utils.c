#include "../../incs/cub3d.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else 
		return (false);
}

int	absolute_value(int	n)
{
	if (n >= 0)
		return (n);
	else
		return (-n);
}

int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

char	get_map_cell(t_core *core, int x, int y)
{
	int	row_len;

	if (x < 0 || y < 0)
		return (' ');
	if (y >= core->map.height)
		return (' ');
	row_len = (int)ft_strlen(core->map.grid[y]);
	if (x >= row_len)
		return (' ');
	return (core->map.grid[y][x]);
}

void	exit_error(t_core *core, char *message)
{
	free_core(core);
	ft_printf("Error\n%s\n", message);
	exit(EXIT_FAILURE);
}
