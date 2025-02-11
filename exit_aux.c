/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <ferda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:45:49 by ferda-si          #+#    #+#             */
/*   Updated: 2025/02/11 15:52:44 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_digit(char *str, int *aux)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' \
			&& str[i] != '+')
		{
			print_error(str, aux);
			return (0);
		}	
		i++;
	}
	return (1);
}

void	exiting(int aux)
{
	if (data()->single_cmd == 1 || aux == 1)
	{
		ft_putendl_fd("exit", 1);
		exit_final();
	}
}
