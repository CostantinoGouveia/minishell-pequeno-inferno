/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinais.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:46:07 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 10:46:47 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		data()->exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		data()->signal = 0;
		data()->is_exec_all = 0;
	}
}

void	handle_sigint_hd(int sig)
{
	if (sig == SIGINT)
	{
		data()->exit_status = 130;
		write(1, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		data()->signal = 0;
		data()->is_exec_all = 0;
	}
}

void	handle_signext(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		return ;
}

void	handle_sigint_clean(int sig)
{
	(void) sig;
	clean_newline();
	close(data()->h_fd);
	exit(data()->exit_status);
}

int	clean_newline(void)
{
	close_fds();
	free_arr(getevarr()->envp);
	free_struct(data()->exec);
	free_envp(data()->envp);
	return (0);
}
