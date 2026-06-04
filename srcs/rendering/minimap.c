#include "../../incs/cub3d.h"


static void	draw_rect(t_core *core, int start_x, int start_y, int color);
static int	cell_color(char c);
static void	draw_cell(t_core *core, int x, int y);
void	draw_tiles(t_core *core);
void	draw_player_dot(t_core *core);
void	draw_dir_line(t_core *core);

void	draw_minimap(t_core *core)
{
	draw_tiles(core);
	draw_player_dot(core);
	draw_dir_line(core);
}

void	draw_dir_line(t_core *core)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;
	int		i;

	x = core->minimap.offset_x + (core->player.x + 0.5f) * core->minimap.tile_size;
	y = core->minimap.offset_y + (core->player.y + 0.5f) * core->minimap.tile_size;
	step_x = core->player.dir_x;
	step_y = core->player.dir_y;

	i = 0;
	while (i < 10) // 10 - line size
	{
		put_pixel(core, (int)x, (int)y, 0xFFFF8F);
		x += step_x;
		y += step_y;
		i++;
	}
}

static void	draw_player_collision_zone(t_core *core, int center_x, int center_y)
{
	int	buffer_pixels;
	int	x;
	int	y;

	buffer_pixels = (int)(COLLISION_BUFFER * core->minimap.tile_size);
	y = center_y - buffer_pixels;
	while (y <= center_y + buffer_pixels)
	{
		x = center_x - buffer_pixels;
		while (x <= center_x + buffer_pixels)
		{
			put_pixel(core, x, y, 0x00FF6600);
			x++;
		}
		y++;
	}
}

void	draw_player_dot(t_core *core)
{
	int	x;
	int	y;

	x = core->minimap.offset_x
		+ (int)((core->player.x + 0.5) * core->minimap.tile_size);
	y = core->minimap.offset_y
		+ (int)((core->player.y + 0.5) * core->minimap.tile_size);
	draw_player_collision_zone(core, x, y);
	draw_rect(core, x - 4, y - 4, 0x00FF0000);
}

void	draw_tiles(t_core *core)
{
	int	x;
	int	y;

	y = 0;
	while (y < core->map.height && core->map.grid[y])
	{
		x = 0;
		while (x < core->map.width)
			draw_cell(core, x++, y);
		y++;
	}
}

static void	draw_rect(t_core *core, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < core->minimap.tile_size)
	{
		x = 0;
		while (x < core->minimap.tile_size)
			put_pixel(core, start_x + x++, start_y + y, color);
		y++;
	}
}

static void	draw_cell(t_core *core, int x, int y)
{
	int		rowlen;
	int		color;
	char	cell;

	rowlen = (int)ft_strlen(core->map.grid[y]);
	if (x < rowlen)
		cell = core->map.grid[y][x];
	else 
		cell = ' ';
	color = cell_color(cell);
	if (color == -1)
		return ;
	draw_rect(core,
			core->minimap.offset_x + x * core->minimap.tile_size, 
			core->minimap.offset_y + y * core->minimap.tile_size,
			color);
}

static int	cell_color(char c)
{
	if (c == '1')
		return (0x00FFFFFF);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0x00333333);
	return (-1);
}

//void	draw_line(t_core *core)
//{
//	int	span[2];
//	int	dir[2];
//	int	err[2];
//
//	// TODO - complete function
//}
