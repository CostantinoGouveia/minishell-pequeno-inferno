/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:13:47 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/07 10:52:36 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_v(t_command *command, int infile, int outfile)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (command->is_exec == 1 && data()->is_exec_all == 1)
	{
		command->pid = fork();
		if (command->pid == 0)
		{
			signal(SIGQUIT, handle_signext);
			signal(SIGINT, handle_signext);
			ft_dup2(command, infile, outfile);
			if (command->path \
			&& execve(command->path, command->args, getevarr()->envp) == -1)
			{
				if (command && command->args[0])
				{
					ft_putstr_fd(command->args[0], STDERR_FILENO);
					ft_putendl_fd(" command not found!", STDERR_FILENO);
				}
			}
			else
			{
				if (command && command->args[0])
				{
					ft_putstr_fd(command->args[0], STDERR_FILENO);
					ft_putendl_fd(" command not found!", STDERR_FILENO);
				}
			}
			clean_newline();
			exit(127);
		}
	}
	if (infile != 0)
		close(infile);
	if (outfile != 1)
		close(outfile);
	return (1);
}

int	dec_infile(t_command *command, int infile)
{
	if (command->infile_fd != -1)
	{
		if (infile != 0)
			close(infile);
		infile = command->infile_fd;
	}
	return (infile);
}

int	dec_outfile(t_command *command, int outfile)
{
	if (command->outfile_fd != -1)
	{
		outfile = command->outfile_fd;
		if (command->fd[1] != -1)
			close(command->fd[1]);
	}
	else if (command->next)
		outfile = command->fd[1];
	else if (command->fd[1] != -1)
		close(command->fd[1]);
	return (outfile);
}

void	executor(t_command *head)
{
	t_command	*current;
	int			infile;
	int			outfile;

	infile = 0;
	current = head;
	while (current)
	{
		outfile = 1;
		if (current->next && pipe(current->fd) == -1)
		{
			ft_putendl_fd("minishell: pipe error", STDERR_FILENO);
			clean_newline();
			break ;
		}
		outfile = dec_outfile(current, outfile);
		infile = dec_infile(current, infile);
		if (current->args && is_builtin(current->args[0]))
			builtins(current, infile, outfile);
		else
			exec_v(current, infile, outfile);
		infile = current->fd[0];
		current = current->next;
	}
	wait_all(head);
}
