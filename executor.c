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

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				data()->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data()->exit_status = WTERMSIG(status) + 128;
		}
	}
}


static int exec_v(t_command *command, int infile, int outfile)
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
            if(command->path && execve(command->path, command->args, getevarr()->envp) == -1)
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

int is_builtin(char *cmd)
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

void builtins(t_command *command, int infile, int outfile)
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

int dec_infile(t_command *command, int infile)
{
    if(command->infile_fd != -1)
    {
        if (infile != 0)
            close(infile);
        infile = command->infile_fd;
    }
    return (infile);
}

int dec_outfile(t_command *command, int outfile)
{
    if(command->outfile_fd != -1)
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


void executor(t_command *head)
{
    t_command *current;
    int infile;
    int outfile;

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