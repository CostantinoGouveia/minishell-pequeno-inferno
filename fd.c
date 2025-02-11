/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <ferda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:51:33 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/11 12:18:32 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open_redirect(t_command *command, int i)
{
	if (command->prompt->tokens_id[i] == INFILE_ID)
		ft_infile_id(command, i);
	else if (command->prompt->tokens_id[i] == OUTFILE_ID)
		ft_outfile_id(command, i);
	else if (command->prompt->tokens_id[i] == APPEND_ID)
		append_id(command, i);
}

static void	error_msg(char *token)
{
	close(data()->h_fd);
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	ft_putline_h(t_command *current, int i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || \
		ft_strncmp(line, current->prompt->tokens[i], \
		ft_strlen(current->prompt->tokens[i]) + 1) == 0)
		{
			if (!line)
				error_msg(current->prompt->tokens[i]);
			free(line);
			break ;
		}
		ft_putendl_fd(line, data()->h_fd);
	}
	close(data()->h_fd);
	exit(0);
}

int	ft_open_here_doc(t_command *current)
{
	int		i;
	int		fd;
	int		pid;

	i = -1;
	while (current->prompt->tokens[++i])
	{
		if (current->prompt->tokens_id[i] == HEREDOC_ID)
		{
			if (current->infile_fd != -1)
				close(current->infile_fd);
			pid = fork();
			signal(SIGINT, handle_sigint_hd);
			if (pid == 0)
			{
				signal(SIGINT, handle_sigint_clean);
				fd = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
				data()->h_fd = fd;
				ft_putline_h(current, i);
			}
			waitpid(pid, NULL, 0);
			return (open_heredoc(current), current->is_exec);
		}
	}
	return (current->is_exec);
}
