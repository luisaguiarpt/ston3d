#include "../../incs/cub3d.h"

void	rotate_dir(t_core *core, int turn_dir)
{
	float	angle;
	float	cos;
	float	sin;
	float	old_dir_x;

	angle = (float)DEGREES_PER_PRESS * (float)M_PI / 180.0f;
	if (turn_dir < 0)
		angle = -angle;
	cos = cosf(angle);
	sin = sinf(angle);
	old_dir_x = core->player.dir_x;
	core->player.dir_x = core->player.dir_x * cos - core->player.dir_y * sin;
	core->player.dir_y = old_dir_x * sin + core->player.dir_y * cos;
}

int	handle_input(int keysym, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (keysym == XK_Escape)
	{
		free_core(core);
		exit(EXIT_FAILURE);
	}
	else if (keysym == XK_Left)
		rotate_dir(core, -1);
	else if (keysym == XK_Right)
		rotate_dir(core, 1);
	return (0);
}
