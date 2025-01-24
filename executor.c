#include "minishell.h"

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
    /*else if (ft_strcmp(command->args[0], "cd") == 0)
        ft_cd(command->args);
    else if (ft_strcmp(command->args[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(command->args[0], "export") == 0)
        ft_export(command->args);
    else if (ft_strcmp(command->args[0], "unset") == 0)
        ft_unset(command->args);
    else if (ft_strcmp(command->args[0], "env") == 0)
        ft_env();*/
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
        infile = dec_infile(current, infile);
        outfile = dec_outfile(current, outfile);
        if (current->args && is_builtin(current->args[0]))
            builtins(current, infile, outfile);
        else
            printf("execve\n");
        infile = current->fd[0];
        current = current->next;
    }
    free_struct(head);
}