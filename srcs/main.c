#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	t_core	core;

	if (ac != 2)
	{
		ft_printf("usage: ./cub3d <path_to_map>\n");
		exit(EXIT_FAILURE);
	}
	init_core(&core);
	parse_cub_file(&core, av[1]);
	validate_map(&core);
	init_mlx(&core);
	mlx_hook(core.win, 2, 1L << 0, (int (*)())(void *)handle_input_press, &core);
	mlx_hook(core.win, 2, 1L << 1, (int (*)())(void *)handle_input_release, &core);
	mlx_loop_hook(core.mlx, (int (*)())(void *)game_loop, &core);
	mlx_loop(core.mlx);
	return (0);
}
