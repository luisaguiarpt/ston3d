#include "../../incs/cub3d.h"

void	clear_image(t_core *core, int color);

void	put_pixel(t_core *core, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return;
	dst = core->img_addr + (y * core->line_len + x * (core->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_core *core)
{
	clear_image(core, 0x8ace00);
	draw_3d(core);
	draw_minimap(core);
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
