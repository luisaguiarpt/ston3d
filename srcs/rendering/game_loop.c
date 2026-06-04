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
	float	old_plane_x;

	angle = (float)DEGREES_PER_PRESS * (float)M_PI / 180.0f;
	if (turn_dir > 0)
		angle = -angle;
	cos = cosf(angle);
	sin = sinf(angle);
	old_dir_x = core->player.dir_x;
	core->player.dir_x = core->player.dir_x * cos - core->player.dir_y * sin;
	core->player.dir_y = old_dir_x * sin + core->player.dir_y * cos;
	old_plane_x = core->player.plane_x;
	core->player.plane_x = core->player.plane_x * cos - core->player.plane_y * sin;
	core->player.plane_y = old_plane_x * sin + core->player.plane_y * cos;
}

static int	is_wall_at(t_core *core, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
	if (map_x >= core->map.width)
		return (1);
	if ((int)ft_strlen(core->map.grid[map_y]) <= map_x)
		return (1);
	return (core->map.grid[map_y][map_x] == '1');
}

static int	check_collision(t_core *core, float new_x, float new_y)
{
	float	test_x;
	float	test_y;

	test_x = new_x + COLLISION_BUFFER;
	test_y = new_y + COLLISION_BUFFER;
	if (is_wall_at(core, test_x, test_y))
		return (1);
	test_x = new_x - COLLISION_BUFFER;
	test_y = new_y + COLLISION_BUFFER;
	if (is_wall_at(core, test_x, test_y))
		return (1);
	test_x = new_x + COLLISION_BUFFER;
	test_y = new_y - COLLISION_BUFFER;
	if (is_wall_at(core, test_x, test_y))
		return (1);
	test_x = new_x - COLLISION_BUFFER;
	test_y = new_y - COLLISION_BUFFER;
	if (is_wall_at(core, test_x, test_y))
		return (1);
	return (0);
}

void	move_forward(t_core *core)
{
	if (core->input.w == true)
	{
		float	new_x = core->player.x + core->player.dir_x * SPEED;
		float	new_y = core->player.y + core->player.dir_y * SPEED;
		
		if (!check_collision(core, new_x, new_y))
		{
			core->player.x = new_x;
			core->player.y = new_y;
		}
	}
}

void	move_backward(t_core *core)
{
	if (core->input.s == true)
	{
		float	new_x = core->player.x - core->player.dir_x * SPEED;
		float	new_y = core->player.y - core->player.dir_y * SPEED;
		
		if (!check_collision(core, new_x, new_y))
		{
			core->player.x = new_x;
			core->player.y = new_y;
		}
	}
}

void	strafe_left(t_core *core)
{
	if (core->input.a == true)
	{
		float	new_x = core->player.x + core->player.dir_y * SPEED;
		float	new_y = core->player.y - core->player.dir_x * SPEED;
		
		if (!check_collision(core, new_x, new_y))
		{
			core->player.x = new_x;
			core->player.y = new_y;
		}
	}
}

void	strafe_right(t_core *core)
{
	if (core->input.d == true)
	{
		float	new_x = core->player.x - core->player.dir_y * SPEED;
		float	new_y = core->player.y + core->player.dir_x * SPEED;
		
		if (!check_collision(core, new_x, new_y))
		{
			core->player.x = new_x;
			core->player.y = new_y;
		}
	}
}
