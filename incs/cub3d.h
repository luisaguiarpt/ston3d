/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:41:14 by josepedr          #+#    #+#             */
/*   Updated: 2026/06/25 22:05:36 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "error_msg.h"
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
# include <sys/time.h>

# define FPS_TARGET 60
# define FRAME_TIME (1000 / FPS_TARGET)
# define HEIGHT 720
# define WIDTH 1280
# define SPEED 0.07f
# define WALL_PADDING 0.25f
# define MOUSE_SENSITIVITY 0.0003f
# define DEGREES_PER_PRESS 2
# define FOV 0.66
# define COLLECT_RADIUS 0.5f
# define END_TRIGGER_RADIUS 0.5f

# define SPRITES_BG_COLOR 0xFF00FF // magenta to remove from bg
# define ARM_BOB_SPEED 0.12f
# define ARM_BOB_RANGE 28.0f
# define GATE_OPEN_SPEED 0.005f

# ifndef BONUS // TODO - check if guard necessary
#  define BONUS 0
# endif

typedef enum e_gate_state
{
	GATE_CLOSED,
	GATE_OPENING,
	GATE_OPEN
}	t_gate_state;

typedef struct s_gate
{
	int				x;
	int				y;
	t_gate_state	state;
	float			progress;
}	t_gate;

typedef struct s_collectible
{
	float	x;
	float	y;
	bool	collected;
	double	dist;
	int		type;
}			t_collectible;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_x;
	double	perp_wall_dist;
	double	draw_step;
	int		draw_start;
	int		draw_end;
	int		true_draw_start;
	int		line_height;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	int		tex_x;
	t_img	*tex;
}			t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
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

typedef struct s_sprites
{
	int		curr_left;
	int		curr_right;
	t_img	left_arm[2];
	t_img	right_arm[5];
	t_img	collectibles[3];
	t_img	gate_img;
	t_img	end_card;
}			t_sprites;

typedef struct s_spr_data
{
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
	int		raw_start_x;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	t_img	*tex;
}			t_spr_data;

typedef struct s_textures
{
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	t_img		no_img;
	t_img		so_img;
	t_img		ea_img;
	t_img		we_img;
	int			floor[3];
	int			ceiling[3]; // R, G, B
	int			floor_int;
	int			ceiling_int;
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
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_addr;
	bool			game_ended;
	int				end_time;
	int				num_collectibles;
	int				collected_count;
	int				collected_mask;
	int				bpp;
	int				bpp_bytes;
	int				endian;
	int				line_len;
	double			zbuffer[WIDTH];
	unsigned int	anim_tick;
	t_input			input;
	t_player		player;
	t_map			map;
	t_textures		textures;
	t_sprites		sprites;
	t_minimap		minimap;
	t_ray			ray;
	t_collectible	*collectibles;
	t_gate			gate;
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

// *** RENDERING ***
//	rendering.c
void	put_pixel(t_core *core, int x, int y, int color);
int		render_frame(t_core *core);
//	texture_rendering.c
void	load_textures(t_core *core);
// minimap.c
void	draw_minimap(t_core *core);
// game_loop.c
int		game_loop(void *param);
//raycast.c
void	draw_3d(t_core *core);
int		get_pixel_from_texture(t_img *img, int tex_x, int tex_y);
//sprites.c
void	draw_arms(t_core *core);
// collectibles.c
void	find_collectibles(t_core *core);
void	update_collectibles(t_core *core);
void	render_collectibles(t_core *core);
// gate.c
void	init_gate(t_core *core);
void	find_gate(t_core *core);
void	update_gate(t_core *core);

// *** KEYBINDS ***
// keybinds.c
void	setup_keybinds(t_core *core);
int		handle_input_press(int key, void *param);
int		handle_input_release(int key, void *param);

// *** UTILS ***
// utils.c
bool	is_space(char c);
int		absolute_value(int n);
int		rgb_to_int(int rgb[3]);
void	exit_error(t_core *core, char *message);
// end.c
void	update_end_state(t_core *core);
int		get_current_time(void);


// free/free.c
void	free_core(t_core *core);
void	exit_game(t_core *core, int exit_code);

#endif
