#include "minishell.h"

void    check_open_redirect(t_command *command, int i)
{
    if (command->prompt->tokens_id[i] == INFILE_ID)
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
    else if (command->prompt->tokens_id[i] == OUTFILE_ID)
    {
        if (command->outfile_fd != -1)
		    close(command->outfile_fd);
        command->outfile_fd = open(command->prompt->tokens[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
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
    else if (command->prompt->tokens_id[i] == APPEND_ID)
    {
        if (command->outfile_fd != -1)
		    close(command->outfile_fd);
        command->outfile_fd = open(command->prompt->tokens[i], O_CREAT | O_RDWR | O_APPEND, 0644);
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
}

static void error_msg(char *token)
{
    close(data()->h_fd);
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
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

int ft_open_here_doc (t_command *current)
{
    int i;
    int fd;
    int pid;
    char *line;

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
                while (1)
                {
                    line = readline("> ");
                    if (!line || \
			                    ft_strncmp(line, current->prompt->tokens[i], ft_strlen(current->prompt->tokens[i]) + 1) == 0)
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
            waitpid(pid, NULL, 0);
            open_heredoc(current);
            return (current->is_exec);
        }
    }
    return (current->is_exec);
}

int ft_open_all (t_command *head)
{
    t_command   *current;
    int     i;


    current = head;
    while (current)
    {
        i = -1;
        ft_open_here_doc(current);
        while (current->prompt->tokens[++i])
            check_open_redirect(current, i);
        if(current->infile_fd != -1 && index_heredoc(current) > index_last_infile(current))
        {
            close(current->infile_fd);
            open_heredoc(current);
        }
        current = current->next;
    }
    return (1);
}