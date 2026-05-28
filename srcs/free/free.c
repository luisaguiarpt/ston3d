#include "../../incs/cub3d.h"

static void	free_textures(t_core *core)
{
	if (core->textures.north)
		free(core->textures.north);
	if (core->textures.south)
		free(core->textures.south);
	if (core->textures.east)
		free(core->textures.east);
	if (core->textures.west)
		free(core->textures.west);
	// TODO free ceiling and floor
}

void	free_core(t_core *core)
{
	if (core->mlx)
		free(core->mlx);
	// TODO check if window also needs to be freed
	free_textures(core);
}
