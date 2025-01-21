/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:08:35 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/15 10:08:47 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(need);
	if (*need == '\0')
		return ((char *)hay);
	while (*hay && len >= needle_len)
	{
		if (*hay == *need)
		{
			if (ft_strncmp(hay, need, needle_len) == 0)
				return ((char *)hay);
		}
		hay++;
		len--;
	}
	return (NULL);
}
