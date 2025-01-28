#include "minishell.h"

void free_no_envp(t_envp *no)
{
    free(no->name);
    free(no->value);
    free(no);
}

void ft_unset(char **args)
{
    int i;
    t_envp *current;
    t_envp *tmp;

    i = 0;
    while (args[++i])
    {
        if (!args[i] || !data()->envp)
            return ;
        current = data()->envp;
        if (!ft_strcmp(current->name, args[i]))
        {
            data()->envp = current->next;
            free_no_envp(current);
            return ;
        }
        while (current)
        {
            if (current->next && !ft_strcmp(current->next->name, args[i]))
            {
                tmp = current->next;
                current->next = current->next->next;
                free_no_envp(tmp);
                break ;
            }
            current = current->next;
        }
    }
    data()->exit_status = 0;
}
