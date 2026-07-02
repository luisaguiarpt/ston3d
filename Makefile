CC=cc
# CFLAGS=-Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror -O3 -march=native -g

NAME=cub3d

BONUS = 0

SRCS=srcs/main.c \
	srcs/parsing/parsing.c srcs/parsing/texture_parsing.c srcs/parsing/map_parsing.c \
	srcs/init/init.c \
	srcs/rendering/game_loop.c \
	srcs/parsing/parsing_utils.c srcs/parsing/player_parsing.c srcs/parsing/collectibles_parsing.c \
	srcs/parsing/validation.c srcs/parsing/validation_utils.c \
	srcs/rendering/rendering.c srcs/rendering/minimap.c srcs/rendering/raycast.c srcs/rendering/texture_rendering.c \
	srcs/rendering/sprites.c srcs/rendering/collectibles.c srcs/rendering/gate.c srcs/rendering/player_arms.c \
	srcs/rendering/smoke.c srcs/rendering/shutter_effect.c \
	srcs/input/keybinds.c srcs/input/mouse.c \
	srcs/free/free.c \
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
	make all BONUS=1

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) $(MLX_LINK) $(LIBFT_A) -o $(NAME)

$(MLX_LIB): 
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
