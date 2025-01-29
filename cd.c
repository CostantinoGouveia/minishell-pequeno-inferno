/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 00:37:24 by feden-pe          #+#    #+#             */
/*   Updated: 2025/01/24 14:18:02 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(char *path)
{
	char	*tmp;

	path++;
	tmp = ft_strjoin("/home/", get_value("USER"));
	path = ft_strjoin(tmp, path);
	free(tmp);
	return (path);
}

void	pwd(int outfile)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return ;
	ft_putendl_fd(pwd, outfile);
	data()->exit_status = 0;
}

static void	change_directory(char *path, int print, int outfile)
{
	char	old[PATH_MAX];
	char	new[PATH_MAX];

	getcwd(old, PATH_MAX);
	if (*path == '~')
		path = get_home(path);
	if (chdir(path) == -1)
	{
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
		data()->exit_status = 1;
		return ;
	}
	else
	{
		update_value("OLDPWD", old);
		getcwd(new, PATH_MAX);
		update_value("PWD", new);
	}
	if (print)
		pwd(outfile);
	data()->exit_status = 0;
}

static void	change_home(char *name, int print, int outfile)
{
	char	*path;

	path = get_value(name);
	if (!ft_strcmp(path, "\0"))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(" not set", 2);
	}
	else if (print)
		change_directory(path, 1, outfile);
	else
		change_directory(path, 0, outfile);
}

void	ft_cd(char **args, int outfile)
{
	if (args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		data()->exit_status = 1;
		return ;
	}
	if (!args[1] || !ft_strcmp(args[1], "~"))
		change_home("HOME", 0, outfile);
	else if (!ft_strcmp(args[1], "-"))
		change_home("OLDPWD", 1, outfile);
	else if (args[1][0] == '\0')
	{
		data()->exit_status = 0;
		return ;
	}
	else
		change_directory(args[1], 0, outfile);
}
