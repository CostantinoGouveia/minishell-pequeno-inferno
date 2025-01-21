# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgama <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 10:49:58 by cgama             #+#    #+#              #
#    Updated: 2024/05/14 10:56:45 by cgama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
INC_DIR = includes
OBJ_DIR = .
HEADER = libft.h

SRC_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_putchar_fd.c\
	    ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_striteri.c\
            ft_memset.c ft_substr.c ft_tolower.c ft_toupper.c ft_strnew.c ft_strtrim.c ft_strmapi.c ft_putnbr_fd.c ft_isspace.c\
	    ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strcpy.c ft_strncpy.c ft_putendl_fd.c\
            ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strncat.c ft_strjoin.c ft_split.c ft_itoa.c ft_putstr_fd.c\

SRC_BNOS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c *ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\

OBJ_FILES = $(SRC_FILES:.c=.o)
BOBJ=$(SRC_BNOS:.c=.o)
OBJ_PATHS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

bonus: all $(BOBJ)
	ar rcs $(NAME) $(BOBJ)

$(NAME): $(OBJ_PATHS)
	ar rcs $(NAME) $(OBJ_PATHS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

