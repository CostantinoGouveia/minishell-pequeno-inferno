/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:23:24 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 11:14:35 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_no_envp(t_envp *no)
{
	free(no->name);
	free(no->value);
	free(no);
}

void	ft_unset_1(char **args, int i, t_envp *current)
{
	t_envp	*tmp;

	while (current)
	{
		if (current->next && !ft_strcmp(current->next->name, args[i]))
		{
			tmp = current->next;
			current->next = current->next->next;
			free_no_envp(tmp);
			break ;
		}
		current = current->next;
	}
}

void	ft_unset(char **args)
{
	t_envp	*current;
	int		i;

	i = 0;
	while (args[++i])
	{
		if (!args[i] || !data()->envp)
			return ;
		current = data()->envp;
		if (!ft_strcmp(current->name, args[i]))
		{
			data()->envp = current->next;
			free_no_envp(current);
			return ;
		}
		ft_unset_1(args, i, current);
	}
	data()->exit_status = 0;
}
