/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:57:08 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/14 16:12:21 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{	
	char			*temp;
	unsigned int	i;

	i = 0;
	temp = malloc(n);
	if (!temp)
		return (NULL);
	ft_memcpy(temp, src, n);
	while (i < n)
	{
		((char *)dest)[i] = temp[i];
		i++;
	}
	free(temp);
	return (dest);
}
