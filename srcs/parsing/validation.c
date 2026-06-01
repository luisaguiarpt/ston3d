#include "../../incs/cub3d.h"

int	locate_player(t_core *core);

int	validate_map(t_core *core)
{
	char **validation_map;
	validation_map = copy_map(core->map.grid); // create this function
	flood_fill(core->player.y, core->player.x, core->map.grid, core);
	return (0);
}

int	flood_fill(int	y, int x, char **grid, t_core *core)
{
	if (y > core->map.height || x > core->map.width)
		return (1);
	if (grid[y][x] == ' ')
		return (1);
}
