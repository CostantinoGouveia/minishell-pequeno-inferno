/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:04:07 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/07 10:04:09 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_exec(char *envp[])
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*add_name(char *str)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new = ft_calloc(i + 1, sizeof(char));
	while (--i >= 0)
		new[i] = str[i];
	return (new);
}

char	*add_value(char *str)
{
	char	*curr;

	curr = str;
	if (!curr)
		return (NULL);
	while (*curr && *curr != '=')
		curr++;
	if (*curr == '\0')
		return (NULL);
	curr++;
	return (curr);
}

t_envp	*insert_end_envp(t_envp **head)
{
	t_envp	*new_node;
	t_envp	*current;

	new_node = ft_calloc(1, sizeof(t_envp));
	if (!new_node)
		exit_final();
	if (!*head)
	{
		*head = new_node;
		return (new_node);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
	return (new_node);
}

void	fill_envp(t_envp **getev, char **envp)
{
	int		i;
	t_envp	*new_node;

	i = 0;
	while (envp && envp[i])
	{
		new_node = insert_end_envp(getev);
		new_node->name = add_name(envp[i]);
		new_node->value = ft_strdup(add_value(envp[i]));
		i++;
	}
}
