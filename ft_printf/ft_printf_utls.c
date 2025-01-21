/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:09:22 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/25 03:09:25 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_d(int nb, int i)
{
	long	n;

	n = (long)nb;
	if (n < 0)
	{
		n *= -1;
		i = ft_putchar_i('-', i);
	}
	if (n >= 0 && n < 10)
		i = ft_putchar_i(n + '0', i);
	else
	{
		i = ft_print_d(n / 10, i);
		i = ft_putchar_i(n % 10 + '0', i);
	}
	return (i);
}

int	ft_print_u(unsigned int nb, int i)
{
	unsigned long	n;

	n = (unsigned long)nb;
	if (n < 10)
		i = ft_putchar_i(n + '0', i);
	else
	{
		i = ft_print_d(n / 10, i);
		i = ft_putchar_i(n % 10 + '0', i);
	}
	return (i);
}

int	ft_print_x(unsigned int nb, int i, int dec)
{
	unsigned int	u;

	u = (unsigned int)nb;
	if (u == 0)
		i = ft_putchar_i('0', i);
	else if (u >= 16)
	{
		i = ft_print_x(u / 16, i, dec);
		i = ft_print_x(u % 16, i, dec);
	}
	else
	{
		if (u <= 9)
			i = ft_putchar_i(u + '0', i);
		else
		{
			if (dec == 0)
				i = ft_putchar_i(u + 'a' - 10, i);
			else
				i = ft_putchar_i(u + 'A' - 10, i);
		}
	}
	return (i);
}

int	ft_print_hex(uintptr_t u, int i)
{
	if (u == 0)
		i = ft_putchar_i('0', i);
	else if (u >= 16)
	{
		i = ft_print_hex(u / 16, i);
		i = ft_print_hex(u % 16, i);
	}
	else
	{
		if (u <= 9)
			i = ft_putchar_i(u + '0', i);
		else
			i = ft_putchar_i(u + 'a' - 10, i);
	}
	return (i);
}

int	ft_print_memory(uintptr_t u, int i)
{
	if (u == 0)
	{
		write(1, "(nil)", 5);
		i += 5;
	}
	else
	{
		write(1, "0x", 2);
		i += 2;
		i = ft_print_hex(u, i);
	}
	return (i);
}
