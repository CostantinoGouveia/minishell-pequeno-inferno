/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:53:29 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:07:13 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr && arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_envp(t_envp *head)
{
	t_envp	*current;
	t_envp	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	head = NULL;
}

void	free_struct(t_command *head)
{
	t_command	*current;
	t_command	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free_arr(tmp->args);
		free(tmp->path);
		free_prompt2(tmp->prompt);
		free(tmp);
	}
	head = NULL;
	free(head);
}

void	unlink_heredoc(void)
{
	if (access("/tmp/here_doc", F_OK) == 0)
		unlink("/tmp/here_doc");
}

void	cmdline_utils(char **line)
{
	free(*line);
	*line = NULL;
	unlink_heredoc();
}
