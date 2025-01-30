#include "minishell.h"
static int	is_open_quotes(char *token);

char	**lexer_sintax_error(char *s1)
{
	char	*s2;
	char	*s3;
	char	**arr;

	arr = NULL;
	s2 = str_spaces_end(s1);
	s3 = split_pipes(s2);
	free(s2);
	s2 = split_redirects(s3);
	free(s3);
	replace_spaces(s2);
	arr = ft_split(s2, '\2');
	space_end(arr);
	free(s2);
	return (arr);
}

/* FOR DEUGB USE: print_tokens(lst); */
int	sintax_errors(char *line)
{
	char		**tokens;
	t_token		*lst;

	lst = NULL;
	tokens = lexer_sintax_error(line);
	parser_tokens(&lst, tokens);
	free_arr(tokens);
	if (handle_pipe_err(lst))
		return (2);
	else if (handle_big_redir(lst))
		return (2);
	else if (handle_newline_err(lst))
		return (2);
	if (handle_quotes_err(lst))
		return (2);
	free_tokens(&lst);
	return (0);
}

int	msg_error(t_token *lst, char *type_err, int exit_status)
{
	data()->exit_status = 2;
	ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
	ft_putstr_fd("near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(type_err, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free_tokens(&lst);
	return (exit_status);
}

int	is_redirect(char *token)
{
	if (!ft_strcmp(token, INFILE) || !ft_strcmp(token, OUTFILE) \
		|| !ft_strcmp(token, APPEND) || !ft_strcmp(token, HERE_DOC))
		return (0);
	return (1);
}
int	handle_quotes_err(t_token *lst)
{
	char	quotes;
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		quotes = is_open_quotes(curr->token);
		if (quotes)
			return (msg_error(lst, (char []){quotes, '\0'}, 1));
		curr = curr->next;
	}
	return (0);
}

int	handle_big_redir(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (!ft_strncmp(curr->token, ">>>", 3))
			return (msg_error(lst, ">", 1));
		else if (!ft_strncmp(curr->token, "<<<", 3))
			return (msg_error(lst, "<", 1));
		else if (!ft_strncmp(curr->token, ">><", 3))
			return (msg_error(lst, "<", 1));
		else if (!ft_strncmp(curr->token, "<<>", 3))
			return (msg_error(lst, ">", 1));
		else if (!ft_strncmp(curr->token, "<>", 2))
			return (msg_error(lst, ">", 1));
		else if (!ft_strncmp(curr->token, "><", 2))
			return (msg_error(lst, "<", 1));
		curr = curr->next;
	}
	return (0);
}

int	handle_newline_err(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (!is_redirect(curr->token) && \
			(curr->prev == NULL && curr->next == NULL))
			return (msg_error(lst, "newline", 1));
		else if (!is_redirect(curr->token) && \
			(curr->next == NULL))
			return (msg_error(lst, "newline", 1));
		else if (curr->next && (!is_redirect(curr->token) && \
			!is_redirect(curr->next->token)))
			return (msg_error(lst, curr->next->token, 1));
		curr = curr->next;
	}
	return (0);
}

int	handle_pipe_err(t_token *lst)
{
	t_token	*curr;

	curr = lst;
	while (curr)
	{
		if (!ft_strcmp(curr->token, PIPE) && \
			(curr->prev == NULL || curr->next == NULL))
			return (msg_error(lst, PIPE, 1));
		else if (curr->next && !is_redirect(curr->token) && \
				!ft_strcmp(curr->next->token, PIPE))
			return (msg_error(lst, PIPE, 1));
		else if (!ft_strncmp(curr->token, "||", 2))
			return (msg_error(lst, PIPE, 1));
		else if (curr->next && !ft_strcmp(curr->token, PIPE) && \
				!ft_strcmp(curr->next->token, PIPE))
			return (msg_error(lst, PIPE, 1));
		else if (curr->next && !ft_strcmp(curr->token, PIPE) && \
				!ft_strcmp(curr->next->token, PIPE))
			return (msg_error(lst, PIPE, 1));
		curr = curr->next;
	}
	return (0);
}

static int	is_open_quotes(char *token)
{
	int		i;
	char	quotes;

	i = 0;
	while (token[i])
	{
		quotes = '\0';
		while (token[i] && (token[i] != '\"' && token[i] != '\''))
			i++;
		if (token[i])
			quotes = token[i++];
		else
			return (0);
		while (token[i] && (token[i] != quotes))
			i++;
		if (!token[i])
			return (quotes);
		else
			i++;
	}
	return (0);
}
