#include "minishell.h"

void print_error(char *str)
{
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

int	check_len(char *str, int len)
{
	if (len > 20 || len < 1)
		return (0);
	if (len == 19)
	{
		if (ft_strncmp(str, "9223372036854775807", 20) > 0)
			return (0);
		if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
			return (0);
	}
	return (1);
}

void ft_exit(char **args)
{
    int i;
    int aux;

    i = 0;
    aux = 0;
    data()->exit_status = 0;
    if (args[1])
    {
        if (args[2])
        {
            ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
            if (data()->exit_status == 0)
                data()->exit_status = 1;
            return ;
        } 
        else 
        {
            while (args[1][i])
            {
                if (!ft_isdigit(args[1][i]) && args[1][i] != '-' && args[1][i] != '+')
                {
                    print_error(args[1]);
                    data()->exit_status = 2;
                    aux = 1;
                    break ;
                }
                i++;
            }
            if (!check_len(args[1], ft_strlen(args[1])) && aux == 0)
            {
                print_error(args[1]);
                data()->exit_status = 2;
                aux = 1;
            }
        }
        if (!args[2] && data()->exit_status == 0)
            data()->exit_status = ft_atoi(args[1]);
    }
    if (data()->single_cmd == 1 || aux == 1)
	{
		ft_putendl_fd("exit", 1);
		exit_final();
	}
}