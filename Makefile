CC=cc
FLAGS=-Wall -Wextra -Werror -g
INCM=mlx
INCL=libft
LIBS=-lmlx -lXext -lX11 -lm

SRCS=srcs/main.c
BONUS_SRCS=

OBJS=$(SRCS:%.c=%.o)
BONUS_OBJS=$(BONUS_SRCS:%.c=%.o)

MLX=mlx/libmlx.a
LIBFT=libft/libft.a
NAME=cub3d

all: $(NAME)

bonus: $(BONUS_OBJS) $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(BONUS_OBJS) $(MLX) $(LIBFT) -o $@ -I$(INCS) $(LIBS)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(MLX) $(LIBFT) -o $@ -I$(INCS) $(LIBS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCM) -I$(INCL)

$(MLX):
	make -C mlx/ all

$(LIBFT):
	make -C libft/ all

clean:
	rm -rf $(OBJS)
	make -C mlx/ clean
	make -C libft/ clean

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
