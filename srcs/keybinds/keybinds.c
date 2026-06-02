#include "../../incs/cub3d.h"

int	handle_input_press(int key, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (key == XK_Escape)
		exit_game(core, EXIT_SUCCESS);
	else if (key == XK_Left)
		core->input.left = true;
	else if (key == XK_Right)
		core->input.right = true;
	else if (key == XK_w)
		core->input.w = true;
	else if (key == XK_a)
		core->input.a = true;
	else if (key == XK_s)
		core->input.s = true;
	else if (key == XK_d)
		core->input.d = true;
	return (0);
}

int	handle_input_release(int key, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (key == XK_Left)
		core->input.left = false;
	else if (key == XK_Right)
		core->input.right = false;
	else if (key == XK_w)
		core->input.w = false;
	else if (key == XK_a)
		core->input.a = false;
	else if (key == XK_s)
		core->input.s = false;
	else if (key == XK_d)
		core->input.d = false;
	return (0);
}
