/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:55:29 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/07 10:55:32 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_command *head)
{
	t_command	*current;
	int			status;
	pid_t		pid;
	pid_t		last_pid;

	current = head;
	status = 0;
	last_pid = find_tail(current)->pid;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				data()->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data()->exit_status = WTERMSIG(status) + 128;
		}
		pid = waitpid(-1, &status, 0);
	}
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	builtins(t_command *command, int infile, int outfile)
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		ft_echo(command->args, outfile, infile);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		ft_cd(command->args, outfile);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		pwd(outfile);
	else if (ft_strcmp(command->args[0], "export") == 0)
		ft_export(command->args, outfile);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		ft_unset(command->args);
	else if (ft_strcmp(command->args[0], "env") == 0)
		ft_env(outfile, 0);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		ft_exit(command->args);
	if (infile != 0)
		close(infile);
	if (outfile != 1)
		close(outfile);
}

void	open_heredoc(t_command *command)
{
	command->infile_fd = open("/tmp/here_doc", O_RDONLY);
	if (command->infile_fd == -1)
	{
		command->is_exec = 0;
		ft_putendl_fd("minishell: error on opening heredoc file" \
		, STDERR_FILENO);
	}
}

int	ft_open_all(t_command *head)
{
	t_command	*current;
	int			i;

	current = head;
	while (current)
	{
		i = -1;
		ft_open_here_doc(current);
		while (current->prompt->tokens[++i])
			check_open_redirect(current, i);
		if (current->infile_fd != -1 && \
		index_heredoc(current) > index_last_infile(current))
		{
			close(current->infile_fd);
			open_heredoc(current);
		}
		current = current->next;
	}
	return (1);
}
