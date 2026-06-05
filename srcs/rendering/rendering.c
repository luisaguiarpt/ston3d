#include "../../incs/cub3d.h"

/*
** Toggle psychedelic post-process effects.
** Set to 1 to enable, 0 to disable each independently.
** Recompile after changing.
*/
#define FX_CHANNEL_ROTATION  0
#define FX_SCANLINE_WARP     0
#define FX_ZOOM_PULSE        1

void	clear_image(t_core *core, int color);
static void	post_process(t_core *core);
static void	scanline_warp(t_core *core);
static void	zoom_pulse(t_core *core);

void	put_pixel(t_core *core, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return;
	dst = core->img_addr + (y * core->line_len + x * (core->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	render_frame(t_core *core)
{
	core->anim_tick++;
	clear_image(core, 0x8ace00);
	draw_3d(core);
	draw_minimap(core);
	if (FX_ZOOM_PULSE)
		zoom_pulse(core);
	if (FX_SCANLINE_WARP)
	scanline_warp(core);
	if (FX_CHANNEL_ROTATION)
	post_process(core);
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	return (0);
}

void	clear_image(t_core *core, int color)
{
	int				y;
	int				x;
	unsigned int	*row;

	if (!core || !core->img_addr)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		row = (unsigned int *)(core->img_addr + y * core->line_len);
		x = 0;
		while (x < WIDTH)
			row[x++] = (unsigned int)color;
		y++;
	}
}

static void	post_process(t_core *core)
{
	int				x;
	int				y;
	unsigned int	*pixel;
	unsigned int	color;
	int				r;
	int				g;
	int				b;
	int				shift;

	shift = (int)(core->anim_tick) & 0xFF;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = (unsigned int *)(core->img_addr
					+ y * core->line_len + x * (core->bpp / 8));
			color = *pixel;
			r = ((int)((color >> 16) & 0xFF) + shift)      & 0xFF;
			g = ((int)((color >> 8)  & 0xFF) + shift * 2)  & 0xFF;
			b = ((int)(color         & 0xFF) + shift * 3)   & 0xFF;
			*pixel = ((unsigned int)r << 16)
				   | ((unsigned int)g << 8)
				   |  (unsigned int)b;
			x++;
		}
		y++;
	}
}

static void	scanline_warp(t_core *core)
{
	static unsigned int	row_buf[WIDTH];
	unsigned int		*row;
	int					shift;
	int					src_x;
	int					x;
	int					y;
	int					tbl_y;
	int					tbl_t;

	y = 0;
	while (y < HEIGHT)
	{
		row = (unsigned int *)(core->img_addr + y * core->line_len);
		tbl_y = (int)((float)y * 3.0f
			* (float)SIN_TABLE_SIZE / (2.0f * (float)M_PI));
		tbl_t = (int)((float)core->anim_tick * 2.0f
			* (float)SIN_TABLE_SIZE / (2.0f * (float)M_PI));
		shift = (int)(LSIN(core, tbl_y + tbl_t) * 20.0f);
		x = 0;
		while (x < WIDTH)
		{
			row_buf[x] = row[x];
			x++;
		}
		x = 0;
		while (x < WIDTH)
		{
			src_x = ((x - shift) % WIDTH + WIDTH) % WIDTH;
			row[x] = row_buf[src_x];
			x++;
		}
		y++;
	}
}

static void	zoom_pulse(t_core *core)
{
	static unsigned int	buf[HEIGHT][WIDTH];
	float				scale;
	float				cx;
	float				cy;
	int					src_x;
	int					src_y;
	int					x;
	int					y;
	int					tbl_t;

	tbl_t = (int)((float)core->anim_tick * 3.0f
		* (float)SIN_TABLE_SIZE / (2.0f * (float)M_PI));
	scale = 1.0f + 0.08f * LSIN(core, tbl_t);
	cx = (float)WIDTH  / 2.0f;
	cy = (float)HEIGHT / 2.0f;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			buf[y][x] = *(unsigned int *)(core->img_addr
					+ y * core->line_len + x * (core->bpp / 8));
			x++;
		}
		y++;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			src_x = (int)(cx + ((float)x - cx) / scale);
			src_y = (int)(cy + ((float)y - cy) / scale);
			src_x = (src_x % WIDTH  + WIDTH)  % WIDTH;
			src_y = (src_y % HEIGHT + HEIGHT) % HEIGHT;
			*(unsigned int *)(core->img_addr
				+ y * core->line_len + x * (core->bpp / 8))
				= buf[src_y][src_x];
			x++;
		}
		y++;
	}
}
