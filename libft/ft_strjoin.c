/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:24:31 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/17 12:54:34 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*aux;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	aux = (char *)malloc(len1 + len2 + 1);
	if (!aux)
		return (NULL);
	while (i < len1)
	{
		aux[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		aux[len1 + i] = s2[i];
		i++;
	}
	aux[len1 + len2] = '\0';
	return (aux);
}
