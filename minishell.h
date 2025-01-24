/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:34:20 by cgouveia          #+#    #+#             */
/*   Updated: 2025/01/24 14:19:27 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <signal.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/ioctl.h>


# define PIPE "|"
# define INFILE "<"
# define OUTFILE ">"
# define APPEND ">>"
# define HERE_DOC "<<"

typedef enum e_token
{
	NO_REDIR,
	INFILE_ID,
	OUTFILE_ID,
	APPEND_ID,
	HEREDOC_ID,
	PIPE_ID,
	ARGS_ID,
}		t_enum_token;

/* For sintax error */
typedef struct s_token
{
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_redirect
{
	t_enum_token		*tokens_id;
	char				**tokens;
	struct s_redirect	*next;
}					t_redirect;

typedef struct s_args
{
	char			*path;
	char			**args;
	struct s_args	*next;
}					t_args;

typedef struct s_prompt
{
	char			*path;
	char			**args;
	t_enum_token	*tokens_id;
	char			**tokens;
	struct s_prompt	*next;
}					t_prompt;


typedef struct s_command
{
	char				*path;
	char				**args;
	int					fd[2];
	int					infile_fd;
	int					outfile_fd;
	pid_t				pid;
	t_prompt			*prompt;
	int					is_last;
	int					is_exec;
	struct s_command	*next;
}						t_command;

typedef struct s_envp
{
	char			*name;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_envparray
{
	char	**envp;
}			t_envparr;

/* DATAS */
typedef struct s_data
{
	char		*path;
	int			exit_status;
	int			h_fd;
	int			signal;
	int			single_cmd;
	int			is_exec_all;
	t_envp		*envp;
	t_command	*exec;
}				t_data;

t_data	*data(void);
char	*add_name(char *str);
char	*add_value(char *str);
t_envp	*insert_end_envp(t_envp **head);
void	fill_envp(t_envp **getev, char **envp);
char	*strtrim_quote(char *str);
void	strtrim_quotes(char **arr);

void	print_arr(char **arr);
void	print_prompt(t_prompt *root);
void	print_args(t_args *root);
void	print_redirects(t_redirect *root);
t_envparr	*getevarr(void);
int	list_len(t_command *head);
char	*create_path(char *dest, char *path, char *command);
void	free_map(char **map);
char	*cmd_path(char *cmd);
char	*etoa(char *name, char *value);
char	**update_env(char **old);
void	update_shlvl(char **envp);
void	no_envp(void);
void	new_envp(char **envp);
char	**envp_exec(char *envp[]);
char	*add_name(char *str);
char	*add_value(char *str);
void	fill_envp(t_envp **getev, char **envp);


t_command	*find_tail(t_command *head);
char	**cpy_arr(char **map);
void	new_struct(t_prompt *prompt, t_command **head);
void	print_commands(t_command *head);
t_command	*init_exec(t_prompt *prompt);

/*execucao*/
void executor(t_command *head);
void builtins(t_command *command, int infile, int outfile);

/*commandos*/
void ft_echo(char **args, int outfile, int infile);
void ft_exit(char **args);
void    ft_cd(char **args, int outfile);
void	pwd(int outfile);

/* Lexer */
int			white_space(char c);
int			just_spaces(char *str);
char		**ft_lexer(char *s1);
char		**lexer_sintax_error(char *s1);
char		*split_pipes(char *s1);
char		*split_redirects(char *s1);
char		*str_spaces_end(char *str);
void		strtrim_quotes(char **arr);
char		*strtrim_quote(char *str);
void		handle_pipe(char *s1, char *s2);
void		handle_redirects(char *s1, char *s2);
void		replace_spaces(char *s1);
void		end_quote(char *sig, char **s1, char **s2);
void		space_end(char **tokens);
int			ft_strcmp(const char *s1, const char *s2);

/*heredoc*/
void	open_heredoc(t_command *command);
int ft_open_here_doc (t_command *current);
int ft_open_all (t_command *head);

/*sinais*/
void	handle_sigint(int sig);
void	handle_sigint_hd(int sig);
void	handle_signext(int sig);
void	handle_sigint_clean(int sig);
int	clean_newline(void);
int	exit_finald(void);
void	close_fds(void);
int	index_heredoc(t_command *current);
int	index_last_infile(t_command *current);

/* Parser */
void	parser_args(t_args **args, char **tokens);
void	fill_args(t_args *node, char **tokens, int *i);
void	fill_tokens(t_redirect *node, char **tokens, int *i, int *j);
void	fill_redirects(t_redirect *node, char **tokens, int *i);
void	fill_null_redirects(t_redirect *node);
int	check_redirects(char **tokens, int i);
void	parser_redirects(t_redirect **redirect, char **tokens);
void	parser_prompt(t_prompt **prompt, t_args *arg, \
						t_redirect *red, char **toks);
void	fill_prompt(t_prompt *node, t_args *arg, t_redirect *red, char **toks);
t_prompt	*insert_end_parser(t_prompt **root);
t_redirect	*insert_end_redirects(t_redirect **root);
t_args	*insert_end_args(t_args **root);
int	count_tokens(char **tokens);

/* erros */
int	handle_quotes_err(t_token *lst);
int	handle_big_redir(t_token *lst);
int	handle_newline_err(t_token *lst);
int	handle_pipe_err(t_token *lst);
char	**lexer_sintax_error(char *s1);
int	sintax_errors(char *line);
int	msg_error(t_token *lst, char *type_err, int exit_status);
int	is_redirect(char *token);
void	init_struct(t_token **tail, t_token **head, char *token);
void	insert_token_end(t_token **head, char *token);
void	parser_tokens(t_token **lst, char **tokens);

/* free */
void	free_prompt(t_prompt **root);
void	free_prompt2(t_prompt *head);
void	free_args(t_args **root);
void	free_redirects(t_redirect **root);
void	free_tokens(t_token **root);
void	free_arr(char **arr);
void	free_envp(t_envp *head);
void	free_struct(t_command *head);

/* Utils */
int	check_str(char *str);
char	*expander_str(char *str);
char	**expander_args(char **args);
void	update_value(char *name, char *value);
char	*get_value(char *name);
int	node_exists(char *name);
t_envp	*get_node(char *name);
int	exit_final(void);

#endif
