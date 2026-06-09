#include "../../incs/cub3d.h"

void	load_xpm(t_core *core, t_img *img, char *path);

void	load_textures(t_core *core)
{
	load_xpm(core, &core->textures.no_img, core->textures.no_path);
	load_xpm(core, &core->textures.so_img, core->textures.so_path);
	load_xpm(core, &core->textures.ea_img, core->textures.ea_path);
	load_xpm(core, &core->textures.we_img, core->textures.we_path);
	core->textures.floor_int = rgb_to_int(core->textures.floor);
	core->textures.ceiling_int = rgb_to_int(core->textures.ceiling);
	if (BONUS)
	{
		load_xpm(core, &core->sprites.left_arm, "sprites/left_arm.xpm");
		load_xpm(core, &core->sprites.right_arm, "sprites/right_arm.xpm");
	}
}

void	load_xpm(t_core *core, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(core->mlx, path, &img->width, &img->height);
	if (!img->img)
		exit_error(core, "failed to load XPM texture");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		exit_error(core, "failed to get texture data address");
}
