/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:26:09 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/20 17:55:55 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static size_t	ft_cont_palav(char const *s, char c)
{
	size_t	cont;
	int		exist_palav;

	cont = 0;
	exist_palav = 0;
	while (*s)
	{
		if (*s != c && !exist_palav)
		{
			exist_palav = 1;
			cont++;
		}
		else if (*s == c)
		{
			exist_palav = 0;
		}
		s++;
	}
	return (cont);
}

static char	*ft_nov_palav(const char *ini, size_t tm)
{
	char	*palav;

	palav = (char *)malloc(tm + 1);
	if (!palav)
		return (NULL);
	ft_strncpy(palav, ini, tm);
	return (palav);
}

static char	**ft_str_split(char **result, char const *s, char c, size_t i)
{
	char const	*ini_palav;
	size_t		tm_palav;

	while (*s)
	{
		if (*s != c)
		{
			tm_palav = 0;
			ini_palav = s;
			while (*s && *s != c)
			{
				tm_palav++;
				s++;
			}
			result[i] = ft_nov_palav(ini_palav, tm_palav);
			if (!result[i])
				return (malloc_error(result));
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		cont_palav;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	cont_palav = ft_cont_palav(s, c);
	result = (char **)malloc((cont_palav + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (ft_str_split(result, s, c, i));
}
