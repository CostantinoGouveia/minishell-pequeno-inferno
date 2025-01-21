#include "minishell.h"

void	init_struct(t_token **tail, t_token **head, char *token)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
	{
		exit(1);
		return ;
	}
	new_node->token = ft_strdup(token);
	new_node->next = NULL;
	new_node->prev = NULL;
	*tail = new_node;
	*head = new_node;
}

void	insert_token_end(t_token **head, char *token)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
	{
		exit(1);
		return ;
	}
	new_node->token = ft_strdup(token);
	new_node->next = NULL;
	new_node->prev = *head;
	(*head)->next = new_node;
	*head = new_node;
}

void	parser_tokens(t_token **lst, char **tokens)
{
	int			i;
	t_token		*tail;
	t_token		*head;

	i = 0;
	tail = NULL;
	head = NULL;
	if (tokens && tokens[i])
		init_struct(&tail, &head, tokens[i++]);
	while (tokens && tokens[i])
	{
		insert_token_end(&head, tokens[i++]);
	}
	*lst = tail;
}
