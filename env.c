/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:14:58 by ferda-si          #+#    #+#             */
/*   Updated: 2025/01/29 16:15:04 by ferda-si         ###   ########.fr       */
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

void	ft_env(int outfile, int dec)
{
	t_envp	*current;

	current = data()->envp;
	while (current)
	{
		if (dec == 1)
		{
			ft_putstr_fd("declare -x ", outfile);
			ft_putstr_fd(current->name, outfile);
		}
		if (current->value)
		{
			if (dec == 0)
				ft_putstr_fd(current->name, outfile);
			if (dec == 0)
				ft_putstr_fd("=", outfile);
			if (dec == 1)
				ft_putstr_fd("=\"", outfile);
			ft_putstr_fd(current->value, outfile);
			if (dec == 1)ft_putstr_fd("\"", outfile);
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
		ft_env(outfile, 1);
	else if (data()->single_cmd == 1)
	{
		while (args && args[++i])
		{
			name = get_name(args[i]);
			if (!name)
				continue ;
			if (ft_isdigit(name[0]) || in_str(name, '-' ) \
				|| in_str(name, '@') || in_str(name, '?') || \
				(in_str(args[i], '=') && in_str(name, '+')))
			{
				print_error1(name);
			}
			else
				value_export(args, i, name);
			free(name);
		}
	}
}
