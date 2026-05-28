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

void	init_core(t_core *core)
{
	core->mlx = mlx_init();
	if (!core->mlx)
		exit(EXIT_FAILURE);
	init_textures(core);
	init_map(core);
	// init_player(core); TODO - init function

}

int	handle_input(int keysim, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (keysim == XK_Escape)
	{
		mlx_destroy_window(core->mlx, core->win);
		mlx_destroy_display(core->mlx);
		free_core(core);
		exit(EXIT_FAILURE);
	}
	return (0);
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
	core.win = mlx_new_window(core.mlx, WIDTH, HEIGHT, "ston3d");
	if (!core.win)
		exit(EXIT_FAILURE);
	core.img = mlx_new_image(core.mlx, WIDTH, HEIGHT);
	if (!core.img)
		exit(EXIT_FAILURE);
	get_endian(&core);
	core.img_addr = mlx_get_data_addr(core.img, &core.bpp, &core.line_len, &core.endian);
	draw_img(&core, 0x8ace00);
	mlx_key_hook(core.win, handle_input, &core);
	mlx_loop(core.mlx);
	return (0);
}

void	get_endian(t_core *core)
{
	int	a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		core->endian = 0;
	else
		core->endian = 1;
}

void	draw_img(t_core *core, int color)
{
	char	*dst;

	int bytespp = core->bpp / 8;
	for (int y = 0; y < 720; y++)
	{
		for (int x = 0; x < 1280; x++)
		{
			dst = core->img_addr + (y * core->line_len + x * bytespp);
			*(unsigned int *)dst = color;
		}
	}
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
}
