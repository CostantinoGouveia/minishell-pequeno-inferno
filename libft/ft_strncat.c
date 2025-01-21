/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:55:08 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/15 13:55:15 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t	index;
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	index = 0;
	while (src[index] && index < nb)
	{
		ptr[index] = src[index];
		index++;
	}
	ptr[index] = '\0';
	return (dest);
}
