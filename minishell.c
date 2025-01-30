/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:16:01 by cgouveia          #+#    #+#             */
/*   Updated: 2025/01/30 13:28:22 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_process(t_prompt *prompt)
{
	t_command	*exec;

	data()->is_exec_all = 1;
	data()->path = get_value("PATH");
	exec = init_exec(prompt);
	data()->exec = exec;
	ft_open_all(exec);
	executor(exec);
	free_struct(data()->exec);
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

void print_tokens(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        printf("tokens[%d]: %s\n", i, tokens[i]);
        i++;
    }
}
void	init_process(char *line)
{
	char		**tokens;
	t_args		*args;
	t_redirect	*redirect;
	t_prompt	*prompt;

	tokens = ft_lexer(line);
	args = NULL;
	parser_args(&args, tokens);
	redirect = NULL;
	parser_redirects(&redirect, tokens);
	prompt = NULL;
	parser_prompt(&prompt, args, redirect, tokens);
	free_arr(tokens);
	free_args(&args);
	free_redirects(&redirect);
	exec_process(prompt);
}



int	cmdline(char *cmd_line, int ac, char **envp)
{
	if (ac != 1)
		return (ft_putstr_fd("Error: Wrong arguments\n", 2), 0);
	new_envp(envp);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		if (!cmd_line)
			cmd_line = readline("[minishell]$ ");
		if (!cmd_line)
			exit_finald();
		if (!just_spaces(cmd_line))
		{
			free(cmd_line);
			cmd_line = NULL;
		}
		else
		{
			if (cmd_line && *cmd_line)
				add_history(cmd_line);
			if (!sintax_errors(cmd_line) && ft_strlen(cmd_line) > 0)
				init_process(cmd_line);
		}
		cmdline_utils(&cmd_line);
	}
	return (0);
}


int main(int ac, char **av, char **envp)
{
    char	*cmd_line;

    (void)av;
	cmd_line = NULL;
	cmdline(cmd_line, ac, envp);
	return 0;
}

