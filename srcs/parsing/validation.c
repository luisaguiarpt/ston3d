#include "../../incs/cub3d.h"

static int	flood_fill(int y, int x, char **grid, t_core *core);
static char	get_grid_cell(char **grid, int x, int y);

int	validate_map(t_core *core)
{
	char	**validation_map;

	validation_map = copy_map(core->map.grid);
	if (!validation_map)
		error_parsing(core, "not enough memory", 0);
	if (flood_fill((int)core->player.y, (int)core->player.x, validation_map, core))
	{
		ft_free_tab(validation_map);
		error_parsing(core, "map must be closed/surrounded by walls", 0);
	}
	ft_free_tab(validation_map);
	return (0);
}

static int	flood_fill(int y, int x, char **grid, t_core *core)
{
	char	cell;

	if (y < 0 || x < 0)
		return (1);
	if (y >= core->map.height || x >= core->map.width)
		return (1);
	cell = get_grid_cell(grid, x, y);
	if (cell == ' ' || cell == '\0')
		return (1);
	if (cell == '1')
		return (0);
	if (cell == 'F')
		return (0);
	grid[y][x] = 'F';
	if (flood_fill(y + 1, x, grid, core))
		return (1);
	if (flood_fill(y - 1, x, grid, core))
		return (1);
	if (flood_fill(y, x + 1, grid, core))
		return (1);
	if (flood_fill(y, x - 1, grid, core))
		return (1);
	return (0);
}

static char	get_grid_cell(char **grid, int x, int y)
{
	int	row_len;

	if (x < 0 || y < 0)
		return (' ');
	if (!grid[y])
		return (' ');
	row_len = (int)ft_strlen(grid[y]);
	if (x >= row_len)
		return (' ');
	return (grid[y][x]);
}
