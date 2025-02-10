/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:02:37 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 13:45:14 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
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
	int	i;
	int	aux;
	char *str;
	i = 0;
	aux = 0;
	data()->exit_status = 0;
	if (args[1])
	{
		str = replace_spaces_1(args[1]);		
		while (str[i])
		{
			if (!ft_isdigit(str[i]) && str[i] != '-' \
			&& str[i] != '+')
			{
				print_error(str);
				data()->exit_status = 2;
				aux = 1;
				return ;
			}
			i++;
		}
		if (!check_len(str, ft_strlen(str)) && aux == 0)
		{
			print_error(str);
			data()->exit_status = 2;
			aux = 1;
			return ;
		}
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
	if (data()->single_cmd == 1 || aux == 1)
	{
		ft_putendl_fd("exit", 1);
		exit_final();
	}
}
