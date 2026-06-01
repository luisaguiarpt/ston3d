#include "../incs/cub3d.h"

void	init_textures(t_core *core)
{
	core->textures.north = NULL;
	core->textures.south = NULL;
	core->textures.east = NULL;
	core->textures.west = NULL;
}

void	init_map(t_core *core)
{
	core->map.grid = NULL;
	core->map.width = 0; // TODO maybe initialize right away
	core->map.height = 0; // TODO maybe initialize right away
}

void	init_minimap(t_core *core)
{
	core->minimap.tile_size = 8;
	core->minimap.offset_x = 1000;
	core->minimap.offset_y = 100;
	core->minimap.width = 10;
	core->minimap.height = 10;
}

void	init_core(t_core *core)
{
	core->win = NULL;
	core->img = NULL;
	core->img_addr = NULL;
	core->bpp = 0;
	core->endian = 0;
	core->line_len = 0;
	init_textures(core);
	init_map(core);
	init_minimap(core);
	// init_player(core); TODO - init function

}

void	init_mlx(t_core *core)
{
	core->mlx = mlx_init();
	if (!core->mlx)
		exit(EXIT_FAILURE);
	core->win = mlx_new_window(core->mlx, WIDTH, HEIGHT, "ston3d");
	if (!core->win)
		exit(EXIT_FAILURE);
	core->img = mlx_new_image(core->mlx, WIDTH, HEIGHT);
	if (!core->img)
		exit(EXIT_FAILURE);
	core->img_addr = mlx_get_data_addr(core->img, &core->bpp, &core->line_len, &core->endian);
}

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
	mlx_hook(core.win, 2, 0, handle_input, &core);
	mlx_loop_hook(core.mlx, render_frame, &core);
	mlx_loop(core.mlx);
	return (0);
}
