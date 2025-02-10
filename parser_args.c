/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:11:22 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:22:26 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_args(t_args **args, char **tokens)
{
	int			i;
	t_args		*new_node;

	i = 0;
	while (tokens[i])
	{
		new_node = insert_end_args(args);
		while (tokens[i] && ft_strcmp(tokens[i], "|"))
		{
			if ((!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") || \
				!ft_strcmp(tokens[i], ">>") || !ft_strcmp(tokens[i], "<<")) \
				&& tokens[i + 1])
				i += 2;
			else
				fill_args(new_node, tokens, &i);
		}
		if (tokens[i])
			i++;
	}
}

void	fill_args(t_args *node, char **tokens, int *i)
{
	int	j;
	int	num_tok;

	j = 0;
	num_tok = count_tokens(tokens);
	node->args = ft_calloc((num_tok + 1), sizeof(char *));
	if (node->args == NULL)
		exit(1);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|"))
	{
		if ((!ft_strcmp(tokens[*i], "<") || !ft_strcmp(tokens[*i], ">") || \
			!ft_strcmp(tokens[*i], ">>") || !ft_strcmp(tokens[*i], "<<")) \
			&& tokens[(*i) + 1])
			(*i) += 2;
		else if (ft_strcmp(tokens[*i], "| "))
			node->args[j++] = ft_strdup(tokens[(*i)++]);
		else
			(*i)++;
	}
	node->args[j] = NULL;
}

int	white_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	just_spaces(char *str)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (white_space(str[i]))
			spaces++;
		i++;
	}
	return (ft_strlen(str) - spaces);
}
