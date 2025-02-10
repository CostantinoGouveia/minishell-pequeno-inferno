/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:16:51 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:21:43 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_spaces_end(char *str)
{
	int		end;
	char	*cpy;

	cpy = ft_strdup(str);
	end = ft_strlen(str) - 1;
	while (end > 0 && white_space(cpy[end]))
	{
		cpy[end] = '\0';
		end--;
	}
	return (cpy);
}

char	**ft_lexer(char *s1)
{
	char	*s2;
	char	*s3;
	char	**arr;

	arr = NULL;
	s2 = str_spaces_end(s1);
	s3 = split_pipes(s2);
	free(s2);
	s2 = split_redirects(s3);
	free(s3);
	replace_spaces(s2);
	arr = ft_split(s2, '\2');
	space_end(arr);
	free(s2);
	return (arr);
}

char	*split_redirects(char *s1)
{
	char	*s2;

	s2 = ft_calloc((ft_strlen(s1) * 2 + 1), sizeof(char));
	handle_redirects(s1, s2);
	replace_spaces(s2);
	return (s2);
}

char	*split_pipes(char *s1)
{
	char	*s2;

	s2 = ft_calloc((ft_strlen(s1) * 2 + 1), sizeof(char));
	handle_pipe(s1, s2);
	replace_spaces(s2);
	return (s2);
}

void	space_end(char **tokens)
{
	int	i;
	int	len;

	i = 0;
	while (tokens[i])
		i++;
	i--;
	len = ft_strlen(tokens[i]) - 1;
	if (tokens[i] && !ft_strcmp(tokens[i], " "))
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
	else if (tokens[i] && tokens[i][len] == ' ')
		tokens[i][len] = '\0';
}
