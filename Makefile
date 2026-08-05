CC=cc

CFLAGS = -Wall -Wextra -Werror -O3 -march=native -g
# for debugging
# CFLAGS = -Wall -Wextra -Werror -g

NAME=cub3d

BONUS = 0
NSFW = 0

SRCS=srcs/main.c \
	srcs/parsing/parsing.c srcs/parsing/texture_parsing.c srcs/parsing/map_parsing.c \
	srcs/init/init_core.c srcs/init/init_imgs.c srcs/init/init_input.c \
	srcs/parsing/parsing_utils.c srcs/parsing/player_parsing.c srcs/parsing/collectibles_parsing.c \
	srcs/parsing/validation.c srcs/parsing/validation_utils.c srcs/parsing/color_parsing.c \
	srcs/raycast/raycast_core.c srcs/raycast/raycast_draw.c srcs/raycast/raycast_gate.c \
	srcs/raycast/raycast_gate_overlay.c srcs/raycast/raycast_texture.c \
	srcs/rendering/rendering.c srcs/rendering/minimap.c srcs/rendering/draw_3d.c srcs/rendering/texture_rendering.c \
	srcs/rendering/sprites.c srcs/rendering/collectibles.c srcs/rendering/gate.c srcs/rendering/player_arms.c \
	srcs/rendering/smoke.c srcs/rendering/shutter_effect.c srcs/rendering/game_loop.c \
	srcs/rendering/load_arms.c srcs/rendering/minimap_markers.c srcs/rendering/player_collision.c \
	srcs/rendering/player_movement.c srcs/rendering/sprite_tex.c \
	srcs/input/keybinds.c srcs/input/mouse.c \
	srcs/free/free_core.c srcs/free/free_sprites.c\
	srcs/utils/utils.c srcs/utils/end.c srcs/utils/collectibles_utils.c srcs/utils/player_utils.c

OBJS=$(SRCS:%.c=%.o)

MLX_DIR=mlx
MLX_LIB=$(MLX_DIR)/libmlx_Linux.a

LIBFT_DIR=libft
LIBFT_A=$(LIBFT_DIR)/libft.a

INCLUDES=-I$(MLX_DIR) -I/usr/include -I$(LIBFT_DIR)

MLX_LINK=-L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -g

all: $(MLX_LIB) $(LIBFT_A) $(NAME)

bonus:
	$(MAKE) fclean all BONUS=1

nsfw:
	$(MAKE) fclean all BONUS=1 NSFW=1

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK) $(LIBFT_A) -o $(NAME)
#	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -DNSFW=$(NSFW) $(OBJS) $(MLX_LINK) $(LIBFT_A) -o $(NAME)

$(MLX_LIB): 
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -DNSFW=$(NSFW) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
