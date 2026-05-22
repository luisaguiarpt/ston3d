SHELL := /bin/bash

CC=cc
CFLAGS=-Wall -Wextra -Werror -I printf -I get_next_line -g

NAME=libft.a

SRC=ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memcpy.c ft_memset.c ft_strlen.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_strnstr.c ft_memcmp.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_atol.c ft_strcmp.c \
	ft_free_tab.c

PRINTF_SRC=printf/ft_printf.c printf/utils.c printf/utils_hex.c \
		   printf/ft_printf_fd.c printf/utils_fd.c

GNL_SRC=get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS=$(SRC:.c=.o)
PRINTF_OBJ=$(PRINTF_SRC:.c=.o)
GNL_OBJ=$(GNL_SRC:.c=.o)

BONUS=ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
	ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUSOBJ=$(BONUS:.c=.o)

ALL_OBJS := $(OBJS) $(PRINTF_OBJ) $(GNL_OBJ)
TOTAL_OBJS := $(words $(ALL_OBJS))
BAR_WIDTH := 50
PROGRESS_FILE := .build_progress_libft

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJ) $(GNL_OBJ)
	@ar rcs $(NAME) $(OBJS) $(PRINTF_OBJ) $(GNL_OBJ)
	@rm -f $(PROGRESS_FILE)

%.o: %.c
	@count=0; \
	if [[ -f "$(PROGRESS_FILE)" ]]; then count=$$(cat "$(PROGRESS_FILE)"); fi; \
	count=$$((count + 1)); \
	echo $$count > "$(PROGRESS_FILE)"; \
	percent=$$((count * 100 / $(TOTAL_OBJS))); \
	filled=$$((count * $(BAR_WIDTH) / $(TOTAL_OBJS))); \
	empty=$$(( $(BAR_WIDTH) - filled )); \
	bar=""; \
	full=""; \
	for ((i=0; i<filled; i++)); do bar+="="; done; \
	for ((i=0; i<empty; i++)); do bar+=" "; done; \
	for ((i=0; i<$(BAR_WIDTH); i++)); do full+="="; done; \
	printf "\r\033[K[%s] %3d%% compiling: %s" "$$bar" "$$percent" "$<"; \
	if [[ $$count -eq $(TOTAL_OBJS) ]]; then \
		printf "\r\033[K[%s] 100%%\n" "$$full"; \
	fi; \
	$(CC) $(CFLAGS) -c "$<" -o "$@"

bonus: $(NAME) $(BONUSOBJ)
	@ar rcs $(NAME) $(BONUSOBJ)

clean:
	@rm -f $(OBJS) $(PRINTF_OBJ) $(GNL_OBJ) $(BONUSOBJ) $(PROGRESS_FILE)

fclean: clean
	@rm -f $(NAME)

re: fclean all
