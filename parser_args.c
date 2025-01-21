#include "minishell.h"

void	parser_args(t_args **args, char **tokens)
{
	int			i;
	t_args		*new_node;

	i = 0;
	while (tokens[i])
	{
		new_node = insert_end_args(args);
		while (tokens[i] && ft_strcmp(tokens[i], "|"))
		{
			if ((!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") || \
				!ft_strcmp(tokens[i], ">>") || !ft_strcmp(tokens[i], "<<")) \
				&& tokens[i + 1])
				i += 2;
			else
				fill_args(new_node, tokens, &i);
		}
		if (tokens[i])
			i++;
	}
}

void	fill_args(t_args *node, char **tokens, int *i)
{
	int	j;
	int	num_tok;

	j = 0;
	num_tok = count_tokens(tokens);
	node->args = ft_calloc((num_tok + 1), sizeof(char *));
	if (node->args == NULL)
		exit(1);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|"))
	{
		if ((!ft_strcmp(tokens[*i], "<") || !ft_strcmp(tokens[*i], ">") || \
			!ft_strcmp(tokens[*i], ">>") || !ft_strcmp(tokens[*i], "<<")) \
			&& tokens[(*i) + 1])
			(*i) += 2;
		else if (ft_strcmp(tokens[*i], "| "))
			node->args[j++] = ft_strdup(tokens[(*i)++]);
		else
			(*i)++;
	}
	node->args[j] = NULL;
}
