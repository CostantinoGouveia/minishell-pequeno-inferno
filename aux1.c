/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:11:52 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/07 10:11:55 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes_err(t_token *lst)
{
	char	quotes;
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		quotes = is_open_quotes(curr->token);
		if (quotes)
			return (msg_error(lst, (char []){quotes, '\0'}, 1));
		curr = curr->next;
	}
	return (0);
}

int	handle_big_redir(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (!ft_strncmp(curr->token, ">>>", 3))
			return (msg_error(lst, ">", 1));
		else if (!ft_strncmp(curr->token, "<<<", 3))
			return (msg_error(lst, "<", 1));
		else if (!ft_strncmp(curr->token, ">><", 3))
			return (msg_error(lst, "<", 1));
		else if (!ft_strncmp(curr->token, "<<>", 3))
			return (msg_error(lst, ">", 1));
		else if (!ft_strncmp(curr->token, "<>", 2))
			return (msg_error(lst, ">", 1));
		else if (!ft_strncmp(curr->token, "><", 2))
			return (msg_error(lst, "<", 1));
		curr = curr->next;
	}
	return (0);
}

int	handle_newline_err(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (!is_redirect(curr->token) && \
			(curr->prev == NULL && curr->next == NULL))
			return (msg_error(lst, "newline", 1));
		else if (!is_redirect(curr->token) && \
			(curr->next == NULL))
			return (msg_error(lst, "newline", 1));
		else if (curr->next && (!is_redirect(curr->token) && \
			!is_redirect(curr->next->token)))
			return (msg_error(lst, curr->next->token, 1));
		curr = curr->next;
	}
	return (0);
}

int	handle_pipe_err(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (!ft_strcmp(curr->token, PIPE) && \
			(curr->prev == NULL || curr->next == NULL))
			return (msg_error(lst, PIPE, 1));
		else if (curr->next && !is_redirect(curr->token) && \
				!ft_strcmp(curr->next->token, PIPE))
			return (msg_error(lst, PIPE, 1));
		else if (!ft_strncmp(curr->token, "||", 2))
			return (msg_error(lst, PIPE, 1));
		else if (curr->next && !ft_strcmp(curr->token, PIPE) && \
				!ft_strcmp(curr->next->token, PIPE))
			return (msg_error(lst, PIPE, 1));
		else if (curr->next && !ft_strcmp(curr->token, PIPE) && \
				!ft_strcmp(curr->next->token, PIPE))
			return (msg_error(lst, PIPE, 1));
		curr = curr->next;
	}
	return (0);
}

void	ft_dup2(t_command *command, int infile, int outfile)
{
	if (command->fd[0] != -1)
		close(command->fd[0]);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		exit(0);
	if (outfile != 1)
		close(outfile);
	if (dup2(infile, STDIN_FILENO) < 0)
		exit(0);
	if (infile != 0)
		close(infile);
}
