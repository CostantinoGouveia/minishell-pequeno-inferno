/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:43:59 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:44:43 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	node_exists(char *name)
{
	t_envp	*current;

	current = data()->envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

t_envp	*get_node(char *name)
{
	t_envp	*current;

	current = data()->envp;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_data	*data(void)
{
	static t_data	d;

	return (&d);
}

t_envparr	*getevarr(void)
{
	static t_envparr	envp;

	return (&envp);
}

int	list_len(t_command *head)
{
	t_command	*current;
	int			i;

	current = head;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
