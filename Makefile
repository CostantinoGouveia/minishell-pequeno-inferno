NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra 
FLAGS_AUX = -lreadline -lhistory
LIBFT = ./libft/libft.a
FTPRINTF = ./ft_printf/libftprintf.a

SRC = minishell.c \
      token.c \
	  erros_sintax.c \
	  free_elements.c \
	  lista_aux.c \
	  parser_args.c \
	  parser_prompt.c \
	  parser_redirect.c \
	  utils.c \
	  expander.c \
	  trim_quotes.c \
	  debugs.c \
	  iniciar_execucao.c \
	  path.c \
	  atualisa_shlvl.c \
	  envp.c \
	
all: $(NAME)

$(NAME): $(SRC:.c=.o)
	@$(MAKE) --no-print-directory -C ./libft
	@echo "\033[1m LIBFT done \033[0m"
	@$(MAKE) --no-print-directory -C ./ft_printf
	@echo "\033[1m FT_PRINTF done \033[0m"
	@$(CC) $(CFLAGS) -lm $(SRC) $(LIBFT) $(FTPRINTF) -o $(NAME) $(FLAGS_AUX)
	@echo "\033[1m Ready to MINISHELL \033[0m"

clean:
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./ft_printf
	@rm -rf $(SRC:.c=.o)
	@echo "\033[1m OBJ deleted \033[0m"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(MAKE) fclean -C ./ft_printf
	@rm -rf $(NAME)
	@echo "\033[1m $(NAME) deleted \033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
