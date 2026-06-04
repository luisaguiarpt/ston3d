#include "../../incs/cub3d.h"

void	exit_game(t_core *core, int exit_code)
{
	free_core(core);
	exit(exit_code);
}

static void	free_map(t_core *core)
{
	if (core->map.grid)
	{
		ft_free_tab(core->map.grid);
		core->map.grid = NULL;
	}
}

static void	free_image(t_core *core, t_img *img)
{
	if (img->img)
		mlx_destroy_image(core->mlx, img->img);
	img->img = NULL;
	img->addr = NULL;
}

static void	free_textures(t_core *core)
{
	if (core->textures.no_path)
		free(core->textures.no_path);
	if (core->textures.so_path)
		free(core->textures.so_path);
	if (core->textures.ea_path)
		free(core->textures.ea_path);
	if (core->textures.we_path)
		free(core->textures.we_path);
	if (core->mlx)
	{
		free_image(core, &core->textures.no_img);
		free_image(core, &core->textures.so_img);
		free_image(core, &core->textures.ea_img);
		free_image(core, &core->textures.we_img);
	}
}

void	free_core(t_core *core)
{
	if (core->mlx && core->img)
		mlx_destroy_image(core->mlx, core->img);
	if (core->mlx && core->win)
		mlx_destroy_window(core->mlx, core->win);
	free_textures(core);
	if (core->mlx)
	{
		mlx_destroy_display(core->mlx);
		free(core->mlx);
	}
	free_map(core);
}
