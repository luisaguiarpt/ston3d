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
# include <math.h>

# define HEIGHT 720
# define WIDTH 1280
# define DEGREES_PER_PRESS 1
# define SPEED 0.01

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
}			t_player;

typedef struct s_minimap
{
	int		tile_size;
	int		offset_x;
	int		offset_y;
	int		width;
	int		height;
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

typedef struct s_input
{
	bool	left;
	bool	right;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	esc;
}				t_input;

typedef struct s_core
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	int			bpp;
	int			endian;
	int			line_len;
	t_input		input;
	t_player	player;
	t_map		map;
	t_textures	textures;
	t_minimap	minimap;
}			t_core;

// INIT
// init.c
void	init_textures(t_core *core);
void	init_map(t_core *core);
void	init_minimap(t_core *core);
void	init_core(t_core *core);
void	init_mlx(t_core *core);

// PARSING
// parsing.c
void	parse_cub_file(t_core *core, char *map_path);
void	error_parsing(t_core *core, char *message, int map_fd);

// VALIDATION
// validation.c
int		validate_map(t_core *core);

// PARSING
// validation_utils.c
char	**copy_map(char **grid);
// textures_parsing.c
void	parse_textures(t_core *core, int map_fd);
// map_parsing.c
void	parse_map(t_core *core, char *map_path, int map_fd);
// parsing_utils.c
bool	is_cub_file(char *line);
bool	is_xpm_file(char *line);
bool	is_empty_line(char *line);
bool	is_valid_line(char *line);
void	remove_newline(char *str);

// RENDERING
//	rendering.c
void	put_pixel(t_core *core, int x, int y, int color);
int		render_frame(t_core *core);
// minimap.c
void	draw_minimap(t_core *core);
// game_loop.c
int		game_loop(void *param);

// KEYBINDS
// keybinds.c
int	handle_input_press(int key, void *param);
int	handle_input_release(int key, void *param);

// utils/utils.c
bool	is_space(char c);

// free/free.c
void	free_core(t_core *core);
void	exit_game(t_core *core, int	exit_code);

#endif
