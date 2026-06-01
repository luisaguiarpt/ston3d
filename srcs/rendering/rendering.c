#include "../../incs/cub3d.h"

void	clear_image(t_core *core, int color);

void	put_pixel(t_core *core, int x, int y, int color)
{
	char	*dst;

	dst = core->img_addr + (y * core->line_len + x * (core->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_img(t_core *core)
{
	static int i = 0;
	int y = 0;
	int x = 0;

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x > 0.2 * WIDTH + i && x < 0.8 * WIDTH && y > 0.2 * HEIGHT)
				put_pixel(core, x, y, 1);
			x++;
		}
		y++;
	}
	i++;
}

void	draw_line(t_core *core)
{
	int	span[2];
	int	dir[2];
	int	err[2];

	// TODO - complete function
}

int	render_frame(t_core *core)
{
	clear_image(core, 0x8ace00);
	draw_img(core);
	mlx_put_image_to_window(core->mlx, core->win, core->img, 0, 0);
	return (0);
}

// TODO - debug only
void	clear_image(t_core *core, int color)
{
	int				y;
	int				x;
	int				bytespp;
	unsigned int	*row;

	if (!core || !core->img_addr)
		return ;

	bytespp = core->bpp / 8;
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
