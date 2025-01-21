/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:30:35 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/20 16:53:28 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	existe_c(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	ini;
	int	fim;

	if (!s1)
		return (NULL);
	ini = 0;
	fim = ft_strlen(s1) - 1;
	while (s1[ini] && existe_c(s1[ini], set))
		ini++;
	while (s1[fim] && existe_c(s1[fim], set))
		fim--;
	if (fim == -1)
		return (ft_substr(s1, ini, 0));
	return (ft_substr(s1, ini, (fim - ini + 1)));
}
