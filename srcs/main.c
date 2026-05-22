#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	t_core	core;
	(void)ac;
	(void)av;

	core.mlx = mlx_init();
	if (!core.mlx)
		exit(EXIT_FAILURE);
	core.win = mlx_new_window(core.mlx, 1280, 720, "ston3d");
	if (!core.win)
		exit(EXIT_FAILURE);
	core.img = mlx_new_image(core.mlx, 1280, 720);
	if (!core.img)
		exit(EXIT_FAILURE);
	get_endian(&core);
	core.img_addr = mlx_get_data_addr(core.img, &core.bpp, &core.line_len, &core.endian);
	draw_img(&core, 0x8ace00ff);
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
	int		i;

	i = 0;
	dst = core->img_addr;
	while (i < (1280 * 720) * (core->bpp / 8))
	{
		dst = core->img_addr + i;
		*(unsigned int *)dst = color;
		i++;
	}
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
}
