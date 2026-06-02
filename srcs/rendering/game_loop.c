#include "../incs/cub3d.h"

void	rotate_dir(t_core *core, int turn_dir);
void	move_forward(t_core *core);
void	move_backward(t_core *core);
void	strafe_left(t_core *core);
void	strafe_right(t_core *core);

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
	if (core->input.s)
		move_backward(core);
	if (core->input.a)
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
	if (turn_dir > 0)
		angle = -angle;
	cos = cosf(angle);
	sin = sinf(angle);
	old_dir_x = core->player.dir_x;
	core->player.dir_x = core->player.dir_x * cos - core->player.dir_y * sin;
	core->player.dir_y = old_dir_x * sin + core->player.dir_y * cos;
}

void	move_forward(t_core *core)
{
	if (core->input.w == true)
	{
		printf("x -> %f | y -> %f\n", core->player.x, core->player.y);
		printf("dir x -> %f | dir y -> %f\n", core->player.dir_x, core->player.dir_y);
		core->player.x += core->player.dir_x * SPEED;
		core->player.y += core->player.dir_y * SPEED;
	}
}

void	move_backward(t_core *core)
{
	if (core->input.s == true)
	{
		printf("x -> %f | y -> %f\n", core->player.x, core->player.y);
		printf("dir x -> %f | dir y -> %f\n", core->player.dir_x, core->player.dir_y);
		core->player.x -= core->player.dir_x * SPEED;
		core->player.y -= core->player.dir_y * SPEED;
	}
}

void	strafe_left(t_core *core)
{
	if (core->input.a == true)
	{
		printf("x -> %f | y -> %f\n", core->player.x, core->player.y);
		printf("dir x -> %f | dir y -> %f\n", core->player.dir_x, core->player.dir_y);
		core->player.x += core->player.dir_y * SPEED;
		core->player.y += core->player.dir_x * SPEED;
	}
}

void	strafe_right(t_core *core)
{
	if (core->input.d == true)
	{
		printf("x -> %f | y -> %f\n", core->player.x, core->player.y);
		printf("dir x -> %f | dir y -> %f\n", core->player.dir_x, core->player.dir_y);
		core->player.x -= core->player.dir_y * SPEED;
		core->player.y -= core->player.dir_x * SPEED;
	}
}
