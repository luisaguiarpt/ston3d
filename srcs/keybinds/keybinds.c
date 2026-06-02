#include "../../incs/cub3d.h"

int	handle_input_press(int key, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (keysym == XK_Escape)
		exit_game(core, EXIT_SUCCESS);
	else if (keysym == XK_Left)
		core->input.left = true;
	else if (keysym == XK_Right)
		core->input.right = true;
	else if (keysym == XK_w)
		core->input.w = true;
	else if (keysym == XK_a)
		core->input.a = true;
	else if (keysym == XK_s)
		core->input.s = true;
	else if (keysym == XK_d)
		core->input.d = true;
	return (0);
}

int	handle_input_release(int key, void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (keysym == XK_Left)
		core->input.left = false;
	else if (keysym == XK_Right)
		core->input.right = false;
	else if (keysym == XK_w)
		core->input.w = false;
	else if (keysym == XK_a)
		core->input.a = false;
	else if (keysym == XK_s)
		core->input.s = false;
	else if (keysym == XK_d)
		core->input.d = false;
	return (0);
}
