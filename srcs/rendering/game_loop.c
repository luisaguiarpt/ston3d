#include "../incs/cub3d.h"

int	game_loop(void *param)
{
	t_core	*core;

	core = (t_core *)param;
	if (core->input.left)
		rotate_dir(core, 1);
	if (core->input.right)
		rotate_dir(core, -1);
	if (core->input.w)
		move_forward(core);
	if (core->input.a)
		move_backwards(core);
	if (core->input.s)
		strafe_left(core);
	if (core->input.d)
		strafe_right(core);
	render_frame(core);
	return (0);
}

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
