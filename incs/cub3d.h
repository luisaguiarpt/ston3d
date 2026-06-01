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
	double	x; // double?? float?? check
	double	y;
	char	dir; // direction the player faces when spawned (N, S, E, W)
}			t_player;

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

typedef enum e_parser_state
{
	PARSER_IN_HEADER,
	PARSER_IN_MAP
}			t_parser_state;

typedef struct s_asset_node
{
	char				*key;
	char				*value;
	int					line_no;
	struct s_asset_node	*next;
}			t_asset_node;

typedef struct s_parse_ctx
{
	t_asset_node	*assets;
	char			*first_map_line;
	int				line_no;
	t_parser_state	state;
}			t_parse_ctx;

typedef enum e_asset_value_type
{
	ASSET_PATH,
	ASSET_RGB
}			t_asset_value_type;

typedef struct s_asset_spec
{
	const char			*key;
	t_asset_value_type	type;
	bool				required;
}			t_asset_spec;

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

void	get_endian(t_core *core);
void	draw_img(t_core *core, int color);

// parsing/parsing.c
void	parse_cub_file(t_core *core, char *map_path);
void	error_parsing(t_core *core, char *message, int map_fd);
void	parser_error(t_core *core, t_parse_ctx *ctx, char *message, int map_fd);
// validation.c
int		validate_map(t_core *core);

// parsing/validation_utils.c
char	**copy_map(char **grid);

// utils/utils.c
bool	is_space(char c);

// free/free.c
void	free_core(t_core *core);

// parsing/textures_parsing.c
void	parse_header(t_core *core, int map_fd, t_parse_ctx *ctx);
void	validate_header_assets(t_core *core, int map_fd, t_parse_ctx *ctx);
void	materialize_header_assets(t_core *core, int map_fd, t_parse_ctx *ctx);
bool	parse_rgb_triplet(char *line, int out[3]);

// parsing/map_parsing.c
void	parse_map(t_core *core, int map_fd, t_parse_ctx *ctx);

// parsing/parsing_dict.c
void		parse_ctx_init(t_parse_ctx *ctx);
void		parse_ctx_free(t_parse_ctx *ctx);
t_asset_node	*parse_dict_find(t_parse_ctx *ctx, const char *key);
bool		parse_dict_insert(t_core *core, t_parse_ctx *ctx, char *key, char *value, int map_fd);

// parsing/parsing_utils.c
bool	is_cub_file(char *line);
bool	is_xpm_file(char *line);
bool	is_empty_line(char *line);
bool	is_valid_line(char *line);
void	remove_newline(char *str);
bool	lex_header_line(char *line, char **key, char **value);
bool	is_header_key(char *key);
bool	is_map_start_line(char *line);

#endif
