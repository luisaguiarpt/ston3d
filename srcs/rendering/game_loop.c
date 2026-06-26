/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:40:09 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 21:54:09 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	rotate_dir(t_core *core, int turn_dir);
void	move_forward(t_core *core);
void	move_backward(t_core *core);
void	strafe_left(t_core *core);
void	strafe_right(t_core *core);

bool	above_frame_rate(void)
{
	static int	last_frame_rendered;
	int			now;

	now = get_current_time();
	if (now - last_frame_rendered < FRAME_TIME)
		return (true);
	last_frame_rendered = now;
	return (false);
}

int	game_loop(void *param)
{
	t_core		*core;

	core = (t_core *)param;
	if (above_frame_rate())
		return (0);
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
	if (BONUS)
	{
		update_collectibles(core);
		update_gate(core);
		update_end_state(core);
	}
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

// static int	is_wall_at(t_core *core, float x, float y)
// {
// 	int	map_x;
// 	int	map_y;
//
// 	map_x = (int)x;
// 	map_y = (int)y;
// 	if (map_y < 0 || map_x < 0)
// 		return (1);
// 	if (map_y >= core->map.height)
// 		return (1);
// 	if (map_x >= core->map.width)
// 		return (1);
// 	if ((int)ft_strlen(core->map.grid[map_y]) <= map_x)
// 		return (1);
// 	return (core->map.grid[map_y][map_x] == '1');
// }
//

static int	is_solid_cell(t_core *core, float x, float y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (1);
	if (map_y >= core->map.height)
		return (1);
	if (map_x >= (int)ft_strlen(core->map.grid[map_y]))
		return (1);
	cell = core->map.grid[map_y][map_x];
	if (cell == '1')
		return (1);
	if (BONUS && cell == 'G' && core->gate.state != GATE_OPEN)
		return (1);
	return (0);
}

static int	collides_x(t_core *core, float new_x)
{
	return (is_solid_cell(core, new_x + WALL_PADDING, core->player.y + WALL_PADDING)
		|| is_solid_cell(core, new_x + WALL_PADDING, core->player.y - WALL_PADDING)
		|| is_solid_cell(core, new_x - WALL_PADDING, core->player.y + WALL_PADDING)
		|| is_solid_cell(core, new_x - WALL_PADDING, core->player.y - WALL_PADDING));
}

static int	collides_y(t_core *core, float new_y)
{
	return (is_solid_cell(core, core->player.x + WALL_PADDING, new_y + WALL_PADDING)
		|| is_solid_cell(core, core->player.x + WALL_PADDING, new_y - WALL_PADDING)
		|| is_solid_cell(core, core->player.x - WALL_PADDING, new_y + WALL_PADDING)
		|| is_solid_cell(core, core->player.x - WALL_PADDING, new_y - WALL_PADDING));
}

// static int	check_collision(t_core *core, float new_x, float new_y)
// {
// 	float	test_x;
// 	float	test_y;
//
// 	test_x = new_x;
// 	test_y = new_y;
// 	if (is_wall_at(core, test_x, test_y))
// 		return (1);
// 	test_x = new_x;
// 	test_y = new_y;
// 	if (is_wall_at(core, test_x, test_y))
// 		return (1);
// 	test_x = new_x;
// 	test_y = new_y;
// 	if (is_wall_at(core, test_x, test_y))
// 		return (1);
// 	test_x = new_x;
// 	test_y = new_y;
// 	if (is_wall_at(core, test_x, test_y))
// 		return (1);
// 	return (0);
// }
//
void	move_forward(t_core *core)
{
	float	new_x;
	float	new_y;

	if (core->input.w == true)
	{
		new_x = core->player.x + core->player.dir_x * SPEED;
		new_y = core->player.y + core->player.dir_y * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}

void	move_backward(t_core *core)
{
	float	new_x;
	float	new_y;

	if (core->input.s == true)
	{
		new_x = core->player.x - core->player.dir_x * SPEED;
		new_y = core->player.y - core->player.dir_y * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}

void	strafe_left(t_core *core)
{
	float	new_x;
	float	new_y;

	if (core->input.a == true)
	{
		new_x = core->player.x + core->player.dir_y * SPEED;
		new_y = core->player.y - core->player.dir_x * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}

void	strafe_right(t_core *core)
{
	float	new_x;
	float	new_y;

	if (core->input.d == true)
	{
		new_x = core->player.x - core->player.dir_y * SPEED;
		new_y = core->player.y + core->player.dir_x * SPEED;
		
		if (!collides_x(core, new_x))
			core->player.x = new_x;
		if (!collides_y(core, new_y))
			core->player.y = new_y;
	}
}
