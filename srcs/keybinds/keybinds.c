#include "../../incs/cub3d.h"

void	rotate_left(t_core *core)
{
	
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
		rotate_left(core);
	else if (keysym == XK_Right)
		rotate_right(core);
	return (0);
}
