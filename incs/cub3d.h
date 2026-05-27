#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}			t_textures;

typedef struct core
{
	void		*mlx;
	void		*win;
	void		*img;
	char		**map_array;
	char		*img_addr;
	int			bpp;
	int			endian;
	int			line_len;
	t_textures	*textures;
}			t_core;

void	get_endian(t_core *core);
void	draw_img(t_core *core, int color);

// check_map/parsing.c
void	parse_map_file(t_core *core, char *map_path);

// utils/utils.c
bool	is_cub_file(char *line);
bool	is_xpm_file(char *line);
bool	is_space(char c);

#endif
