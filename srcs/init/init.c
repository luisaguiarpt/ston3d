#include "../../incs/cub3d.h"

void	init_textures(t_core *core)
{
	core->textures.no_path = NULL;
	core->textures.so_path = NULL;
	core->textures.ea_path = NULL;
	core->textures.we_path = NULL;
	core->textures.no_img.img = NULL;
	core->textures.so_img.img = NULL;
	core->textures.ea_img.img = NULL;
	core->textures.we_img.img = NULL;
	core->textures.no_img.addr = NULL;
	core->textures.so_img.addr = NULL;
	core->textures.ea_img.addr = NULL;
	core->textures.we_img.addr = NULL;
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

void	init_player(t_core *core)
{
	// TODO - initialize core->player values here and
	// create a new funciton for the inputs
	core->input.w = false;
	core->input.a = false;
	core->input.s = false;
	core->input.d = false;
	core->input.left = false;
	core->input.right = false;
}

void	init_core(t_core *core)
{
	core->mlx = NULL;
	core->win = NULL;
	core->img = NULL;
	core->img_addr = NULL;
	core->bpp = 0;
	core->endian = 0;
	core->line_len = 0;
	core->anim_tick = 0;
	init_textures(core);
	init_map(core);
	init_minimap(core);
	init_player(core); //TODO - init function

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
