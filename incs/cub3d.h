#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <X11/keysym.h>

# define HEIGHT 720
# define WIDTH 1280

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
}			t_player;

typedef struct s_minimap
{
	int	tile_size;
	int	offset_x;
	int	offset_y;
}			t_minimap;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			floor[3];
	int			ceiling[3]; // R, G, B
}			t_textures;

typedef struct s_core
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	int			bpp;
	int			endian;
	int			line_len;
	t_player	player;
	t_map		map;
	t_textures	textures;
}			t_core;

// parsing/parsing.c
void	parse_cub_file(t_core *core, char *map_path);
void	error_parsing(t_core *core, char *message, int map_fd);
//
// validation.c
int		validate_map(t_core *core);

// parsing/validation_utils.c
char	**copy_map(char **grid);

// rendering/rendering.c
void	put_pixel(t_core *core, int x, int y, int color);
int		render_frame(t_core *core);


// utils/utils.c
bool	is_space(char c);

// free/free.c
void	free_core(t_core *core);

// parsing/textures_parsing.c
void	parse_textures(t_core *core, int map_fd);

// parsing/map_parsing.c
void	parse_map(t_core *core, char *map_path, int map_fd);

// parsing/parsing_utils.c
bool	is_cub_file(char *line);
bool	is_xpm_file(char *line);
bool	is_empty_line(char *line);
bool	is_valid_line(char *line);
void	remove_newline(char *str);

#endif
