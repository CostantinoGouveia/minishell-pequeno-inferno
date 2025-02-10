/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:35:43 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 14:53:55 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_aux(int outfile, int dec, t_envp *current)
{
	if (dec == 1)
	{
		ft_putstr_fd("declare -x ", outfile);
		ft_putstr_fd(current->name, outfile);
	}
}

void	ft_env(int outfile, int dec)
{
	t_envp	*current;

	current = data()->envp;
	while (current)
	{
		if (dec == 1)
			ft_aux(outfile, dec, current);
		if (current->value)
		{
			if (dec == 0)
				ft_putstr_fd(current->name, outfile);
			if (dec == 0)
				ft_putstr_fd("=", outfile);
			if (dec == 1)
				ft_putstr_fd("=\"", outfile);
			ft_putstr_fd(current->value, outfile);
			if (dec == 1)
				ft_putstr_fd("\"", outfile);
		}
		ft_putstr_fd("\n", outfile);
		current = current->next;
	}
	data()->exit_status = 0;
}

void	value_export(char **args, int i, char *name)
{
	t_envp	*current;
	t_envp	*new_node;

	if (node_exists(name) && get_value(name))
		update_value(name, add_value(args[i]));
	else if (node_exists(name) && in_str(args[i], '='))
	{
		current = get_node(name);
		free(current->value);
		current->value = ft_strdup(add_value(args[i]));
	}
	else if (in_str(args[i], '='))
	{
		new_node = insert_end_envp(&data()->envp);
		new_node->name = ft_strdup(name);
		new_node->value = ft_strdup(add_value(args[i]));
	}
	else if (!in_str(args[i], '='))
	{
		new_node = insert_end_envp(&data()->envp);
		new_node->name = ft_strdup(name);
		new_node->value = NULL;
	}
	data()->exit_status = 0;
}

void	ft_export(char **args, int outfile)
{
	char	*name;
	int		i;

	i = 0;
	if (args && args[i + 1] == NULL)
	{
		ft_env(outfile, 1);
		return ;
	}
	if (data()->single_cmd == 1)
	{
		while (args && args[++i])
		{
			name = get_name(args[i]);
			if (!name)
				continue ;
			if (ft_isdigit(name[0]) || in_str(name, '-' ) \
			|| in_str(name, '@') || in_str(name, '?') || in_str(name, '\'') \
			|| in_str(name, '"') || (in_str(args[i], '=') && in_str(name, '+')))
				print_error1(name);
			else
				value_export(args, i, name);
			free(name);
		}
	}
}
