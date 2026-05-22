#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

typedef struct core
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		bpp;
	int		endian;
	int		line_len;
}				t_core;

void	get_endian(t_core *core);
void	draw_img(t_core *core, int color);

#endif
