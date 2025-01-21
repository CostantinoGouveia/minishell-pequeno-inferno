/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:55:14 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/15 10:55:45 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	is_negative;

	nb = 0;
	is_negative = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			is_negative = -1;
	while (*str >= '0' && *str <= '9')
	{
		if ((nb > INT_MAX / 10)
			|| (nb == INT_MAX / 10 && (*str - '0' > INT_MAX % 10)))
		{
			if (is_negative == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		nb = nb * 10 + (*str++ - '0');
	}
	return (nb * is_negative);
}
