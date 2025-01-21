
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = .
HEADER = ft_prntf.h

SRC_FILES = ft_printf.c ft_printf_utls.c\

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_PATHS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ_PATHS)
	ar rcs $(NAME) $(OBJ_PATHS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

fclean:
	rm -f $(NAME) $(OBJ_FILES) $(BOBJ)

re: fclean all

.PHONY: all clean fclean re

