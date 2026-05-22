#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	t_core	core;
	(void)ac;
	(void)av;

	core.mlx = mlx_init();
	if (!core.mlx)
		exit(EXIT_FAILURE);
	core.win = mlx_new_window(core.mlx, 100, 100, "ston3d");
	if (!core.win)
		exit(EXIT_FAILURE);
	mlx_loop(core.mlx);
}
