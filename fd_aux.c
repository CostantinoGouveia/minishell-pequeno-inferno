/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:16:54 by ferda-si          #+#    #+#             */
/*   Updated: 2025/02/11 12:16:58 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile_id(t_command *command, int i)
{
	if (command->infile_fd != -1)
		close(command->infile_fd);
	command->infile_fd = open(command->prompt->tokens[i], O_RDONLY);
	if (command->infile_fd == -1)
	{
		if (access(command->prompt->tokens[i], F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command->prompt->tokens[i], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			data()->exit_status = 1;
			command->is_exec = 0;
		}
		else if (access(command->prompt->tokens[i], F_OK | R_OK) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command->prompt->tokens[i], STDERR_FILENO);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
			data()->exit_status = 1;
			command->is_exec = 0;
		}
		command->is_exec = 0;
	}
}

void	ft_outfile_id(t_command *command, int i)
{
	if (command->outfile_fd != -1)
		close(command->outfile_fd);
	command->outfile_fd = open(command->prompt->tokens[i], \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (command->outfile_fd == -1)
	{
		if (access(command->prompt->tokens[i], F_OK | W_OK | R_OK) == -1)
		{
			ft_putendl_fd(" Permission denied", 2);
			command->is_exec = 0;
			data()->exit_status = 1;
		}
	}
}

void	append_id(t_command *command, int i)
{
	if (command->outfile_fd != -1)
		close(command->outfile_fd);
	command->outfile_fd = open(command->prompt->tokens[i], \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (command->outfile_fd == -1)
	{
		if (access(command->prompt->tokens[i], F_OK | W_OK | R_OK) == -1)
		{
			ft_putendl_fd(" Permission denied", 2);
			command->is_exec = 0;
			data()->exit_status = 1;
		}
	}
}
