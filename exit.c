/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <ferda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:02:37 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/11 15:45:24 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, int *aux)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	data()->exit_status = 2;
	*aux = 1;
}

int	check_len(char *str, int len)
{
	if (len > 20 || len < 1)
		return (0);
	if (len == 19 || len == 20)
	{
		if (!ft_strncmp(str, "9223372036854775808", 19))
			return (0);
		if (!ft_strncmp(str, "-9223372036854775809", 20))
			return (0);
	}
	return (1);
}

char	*replace_spaces_1(char *s1)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (white_space(s1[i]))
		i++;
	str = malloc(sizeof(char) * (ft_strlen(s1 + i) + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	while (j > 0 && white_space(str[j - 1]))
		j--;
	str[j] = '\0';
	return (str);
}

void	ft_exit(char **args)
{	
	char	*str;
	int		aux;

	aux = 0;
	data()->exit_status = 0;
	if (args[1])
	{
		str = replace_spaces_1(args[1]);
		if (is_valid_digit(str, &aux) == 0)
			return ;
		if (!check_len(str, ft_strlen(str)) && aux == 0)
			return (print_error(str, &aux));
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			if (data()->exit_status == 0)
				data()->exit_status = 1;
			return ;
		}
		if (!args[2] && data()->exit_status == 0)
			data()->exit_status = ft_atoi(str);
	}
	exiting(aux);
}
