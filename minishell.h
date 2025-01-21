/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:34:20 by cgouveia          #+#    #+#             */
/*   Updated: 2025/01/20 15:02:47 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Lexer */
int			white_space(char c);
int			just_spaces(char *str);
char		**ft_lexer(char *s1);
char		**lexer_sintax_error(char *s1);
char		*split_pipes(char *s1);
char		*split_redirects(char *s1);
char		*str_spaces_end(char *str);
void		strtrim_quotes(char **arr);
char		*strtrim_quote(char *str);
void		handle_pipe(char *s1, char *s2);
void		handle_redirects(char *s1, char *s2);
void		replace_spaces(char *s1);
void		end_quote(char *sig, char **s1, char **s2);
void		space_end(char **tokens);
int			ft_strcmp(const char *s1, const char *s2);

#endif
