#include "../../incs/cub3d.h"

void	draw_left_arm(t_core *core, int offset)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	start_x = 0;
	start_y = 400 + offset;
	//start_y = (HEIGHT - core->sprites.left_arm.height + offset);
	y = 0;
	while (y < core->sprites.left_arm.height)
	{
		x = 0;
		while (x < core->sprites.left_arm.width)
		{
			color = get_pixel_from_texture(&core->sprites.left_arm, x, y);
			if (color != SPRITES_BG_COLOR)
				put_pixel(core, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_right_arm(t_core *core, int offset)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;
	int	color;

	start_x = 250;
	start_y = (350 - offset);
	y = 0;
	while (y < core->sprites.right_arm.height)
	{
		x = 0;
		while (x < core->sprites.right_arm.width)
		{
			color = get_pixel_from_texture(&core->sprites.right_arm, x, y);
			if (color != SPRITES_BG_COLOR)
				put_pixel(core, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

int	calculate_animation_offset(t_core *core)
{
	static float	offset;

	if (core->input.w
	 	|| core->input.a
	 	|| core->input.s
	 	|| core->input.d)
		offset += 0.15f; // BOB_SPEED
	return ((int)(sinf(offset) * 28.0f)); // BOB_RANGE
}

void	draw_arms(t_core *core)
{
	int	offset;

	offset = calculate_animation_offset(core);
	draw_left_arm(core, offset);
	draw_right_arm(core, offset);
}
