/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:01:22 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/07 10:01:26 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error1(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data()->exit_status = 1;
}

char	*get_name(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (white_space(str[i]))
		i++;
	if (str[i] == '=')
	{
		print_error1(str);
		return (NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	new = ft_calloc(i + 1, sizeof(char));
	while (--i >= 0)
		new[i] = str[i];
	return (new);
}

int	is_num(char *str)
{
	int	flag;

	if (!str)
		return (0);
	flag = 0;
	if (*str == '-')
		str++;
	while (*str)
	{
		flag = 1;
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (flag);
}

int	in_str(char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			flag = 1;
		i++;
	}
	return (flag);
}
