/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:49:41 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/15 12:49:50 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	total_len;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	total_len = len_dest + len_src;
	if (size <= len_dest)
		return (len_src + size);
	else
	{
		ft_strncat(dest + len_dest, src, size - len_dest - 1);
		return (total_len);
	}
}
