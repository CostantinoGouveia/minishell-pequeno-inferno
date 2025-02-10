/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:18:03 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:18:19 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(char *s1, char *s2)
{
	char	sig;

	sig = 1;
	while (s1 && *s1)
	{
		if (sig == 1)
		{
			if (*s1 != '\0' && *s1 == '|')
			{
				*s2++ = ' ';
				while (*s1 != '\0' && *s1 == '|')
					*s2++ = *s1++;
				if (*s1 != '\0')
					*s2++ = ' ';
			}
			if (s1 && (*s1 == '\"' || *s1 == '\''))
				sig = *s1;
			if (s1 && s2 && *s1)
				*s2++ = *s1++;
		}
		else
			end_quote(&sig, &s1, &s2);
	}
	if (s2)
		*s2 = '\0';
}

void	handle_redirects(char *s1, char *s2)
{
	char	sig;

	sig = 1;
	while (s1 && *s1)
	{
		if (sig == 1)
		{
			if (*s1 != '\0' && (*s1 == '<' || *s1 == '>'))
			{
				*s2++ = ' ';
				while (*s1 != '\0' && (*s1 == '<' || *s1 == '>'))
					*s2++ = *s1++;
				if (*s1 != '\0')
					*s2++ = ' ';
			}
			if (s1 && (*s1 == '\"' || *s1 == '\''))
				sig = *s1;
			if (s1 && s2 && *s1)
				*s2++ = *s1++;
		}
		else
			end_quote(&sig, &s1, &s2);
	}
	if (s2)
		*s2 = '\0';
}

/**
 * Substitui separador
 * echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
 * echo/2"hello      there"/2how/2are/2'you 'doing?/2$USER/2|wc/2-l/2>outfile
*/
void	replace_spaces(char *s1)
{
	char	sig;
	int		i;

	sig = 1;
	i = 0;
	while (s1 && s1[i])
	{
		if (sig == 1)
		{
			while (s1 && white_space(s1[i]) && s1[i + 1] != '\0')
				s1[i++] = '\2';
			if (s1 && s1[i] && (s1[i] == '\"' || s1[i] == '\''))
				sig = s1[i];
		}
		else
		{
			if (sig == '\"' || sig == '\'')
			{
				if (s1 && s1[i] == sig)
					sig = 1;
			}
		}
		i++;
	}
	s1[i] = '\0';
}

void	end_quote(char *sig, char **s1, char **s2)
{
	if (*sig == '\"' || *sig == '\'')
	{
		if (**s1 == *sig)
			*sig = 1;
		*(*s2)++ = *(*s1)++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
