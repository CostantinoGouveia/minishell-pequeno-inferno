/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:14:56 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:15:44 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_final(void)
{
	clean_newline();
	clear_history();
	exit(data()->exit_status);
	return (0);
}

int	exit_finald(void)
{
	free_arr(getevarr()->envp);
	free_envp(data()->envp);
	clear_history();
	ft_putendl_fd("exit", 1);
	exit(data()->exit_status);
	return (0);
}

void	close_fds(void)
{
	size_t	fd;

	fd = 3;
	while (fd < FOPEN_MAX)
	{
		close(fd);
		fd++;
	}
}

int	index_heredoc(t_command *current)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (current->prompt->tokens_id[i++])
	{
		if (current->prompt->tokens_id[i] == HEREDOC_ID)
			ret = i;
	}
	return (ret);
}

int	index_last_infile(t_command *current)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (current->prompt->tokens_id[i++])
	{
		if (current->prompt->tokens_id[i] == INFILE_ID)
			ret = i;
	}
	return (ret);
}
