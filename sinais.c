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