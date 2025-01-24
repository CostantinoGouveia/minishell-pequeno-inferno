#include "minishell.h"

int is_flag_n(char **args, int i, int j, int n_flag)
{
    if (!args || args[1] == NULL)
        return (0);
    while (args[++i])
    {
        j = 0;
        if (args[i][j] == '-')
        {
            j++;
            if (!args[i][j])
				return (n_flag);
            while (args[i][j])
            {
                if (args[i][j] != 'n')
					return (n_flag);
                j++;
            }
        }
        else
            return (n_flag);
        n_flag++;
        j = 0;
    }
    return (n_flag);
}

int is_quote(char *str)
{
    if(!ft_strcmp(str, "\0") || !ft_strcmp(str, "\"\"") || !ft_strcmp(str, "\'\'"))
        return (1);
    return (0);
}

void print_echo(char **args, int outfile, int n_flag)
{
    int i;

    i = 1 + n_flag;
    if(!args[i])
    {
        if (!n_flag)
            ft_putchar_fd('\n', outfile);
        return ;
    }
    while (args[i + 1])
    {
        if (is_quote(args[i]))
            i++;
        else
        {
            ft_putstr_fd(args[i], outfile);
            ft_putchar_fd(' ', outfile);
            i++;
        }
    }
    if (ft_strcmp(args[i], "\0"))
			ft_putstr_fd(args[i], outfile);
	if (!n_flag)
		ft_putchar_fd('\n', outfile);
	data()->exit_status = 0;
}

void ft_echo(char **args, int outfile, int infile)
{
    int i;
    int j;
    int n_flag;

    (void)infile;
    i = 0;
    n_flag = 0;
    j = 0;
    print_echo(args, outfile, is_flag_n(args, i, j, n_flag));
}
