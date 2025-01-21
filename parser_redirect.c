#include "minishell.h"

void	fill_tokens(t_redirect *node, char **tokens, int *i, int *j)
{
	if (!ft_strcmp(tokens[*i], "<") && tokens[(*i) + 1])
	{
		node->tokens_id[*j] = INFILE_ID;
		node->tokens[(*j)++] = strtrim_quote(ft_strdup(tokens[++(*i)]));
	}
	else if (!ft_strcmp(tokens[*i], ">") && tokens[(*i) + 1])
	{
		node->tokens_id[*j] = OUTFILE_ID;
		node->tokens[(*j)++] = strtrim_quote(ft_strdup(tokens[++(*i)]));
	}
	else if (!ft_strcmp(tokens[*i], ">>") && tokens[(*i) + 1])
	{
		node->tokens_id[*j] = APPEND_ID;
		node->tokens[(*j)++] = strtrim_quote(ft_strdup(tokens[++(*i)]));
	}
	else if (!ft_strcmp(tokens[*i], "<<") && tokens[(*i) + 1])
	{
		node->tokens_id[*j] = HEREDOC_ID;
		node->tokens[(*j)++] = strtrim_quote(ft_strdup(tokens[++(*i)]));
	}
}

void	fill_redirects(t_redirect *node, char **tokens, int *i)
{
	int	j;
	int	num_tok;

	j = 0;
	num_tok = count_tokens(tokens);
	node->tokens = ft_calloc((num_tok + 1), sizeof(char *));
	node->tokens_id = ft_calloc((num_tok + 1), sizeof(int));
	if (!node->tokens || !node->tokens_id)
		exit(1);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|"))
	{
		fill_tokens(node, tokens, i, &j);
		(*i)++;
	}
	node->tokens_id[j] = 0;
	node->tokens[j] = NULL;
}

void	fill_null_redirects(t_redirect *node)
{
	node->tokens_id = ft_calloc(1, sizeof(int));
	if (!node->tokens_id)
		exit(1);
	node->tokens_id[0] = NO_REDIR;
	node->tokens = ft_calloc(2, sizeof(char *));
	if (!node->tokens)
		exit(1);
	node->tokens[0] = ft_strdup("(null)");
	node->tokens[1] = NULL;
}

int	check_redirects(char **tokens, int i)
{
	int	j;

	j = i;
	while (tokens[j] && ft_strcmp(tokens[j], "|"))
	{
		if ((!ft_strcmp(tokens[j], "<") || !ft_strcmp(tokens[j], ">") || \
		!ft_strcmp(tokens[j], ">>") || !ft_strcmp(tokens[j], "<<")))
			return (1);
		else
			j++;
	}
	return (0);
}

void	parser_redirects(t_redirect **redirect, char **tokens)
{
	int			i;
	t_redirect	*new_node;	

	i = 0;
	while (tokens[i])
	{
		while (tokens[i] && ft_strcmp(tokens[i], "|"))
		{
			if (check_redirects(tokens, i))
			{
				new_node = insert_end_redirects(redirect);
				fill_redirects(new_node, tokens, &i);
			}
			else
			{
				new_node = insert_end_redirects(redirect);
				fill_null_redirects(new_node);
				while (tokens[i] && ft_strcmp(tokens[i], "|"))
					i++;
			}
		}
		if (tokens[i])
			i++;
	}
}
