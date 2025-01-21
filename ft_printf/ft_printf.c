/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:07:20 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/25 03:07:26 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_i(char c, int i)
{
	i++;
	write(1, &c, 1);
	return (i);
}

int	ft_print_str(const char *s, int i)
{
	if (!s)
	{
		write(1, "(null)", 6);
		i += 6;
	}
	else
	{
		while (*s)
		{
			i = ft_putchar_i(*s, i);
			s++;
		}
	}
	return (i);
}

int	ft_print_dec(const char *formato, int j, int i, va_list args)
{
	if (formato[j] == 's')
		i = ft_print_str(va_arg(args, char *), i);
	if (formato[j] == 'c')
		i = ft_putchar_i(va_arg(args, int), i);
	if (formato[j] == 'p')
		i = ft_print_memory(va_arg(args, unsigned long long), i);
	if (formato[j] == 'd' || formato[j] == 'i')
		i = ft_print_d(va_arg(args, int), i);
	if (formato[j] == 'X')
		i = ft_print_x(va_arg(args, unsigned int), i, 1);
	if (formato[j] == 'x')
		i = ft_print_x(va_arg(args, unsigned int), i, 0);
	if (formato[j] == 'u')
		i = ft_print_u(va_arg(args, unsigned int), i);
	if (formato[j] == '%')
		i = ft_putchar_i('%', i);
	return (i);
}

int	ft_printf(const char *formato, ...)
{
	int		i;
	int		j;
	va_list	args;

	j = 0;
	i = 0;
	va_start(args, formato);
	while (formato[j])
	{
		if (formato[j] == '%')
			i = ft_print_dec(formato, ++j, i, args);
		else
		{
			i = ft_putchar_i(formato[j], i);
		}
		j++;
	}
	return (i);
}
