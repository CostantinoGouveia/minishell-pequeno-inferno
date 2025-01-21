#include "minishell.h"

void	free_prompt(t_prompt **root)
{
	t_prompt	*curr;
	t_prompt	*aux;

	curr = *root;
	while (curr)
	{
		aux = curr;
		curr = curr->next;
		free_arr(aux->args);
		free_arr(aux->tokens);
		free(aux->path);
		free(aux->tokens_id);
		free(aux);
	}
	*root = NULL;
}

void	free_prompt2(t_prompt *head)
{
	free_arr(head->args);
	free_arr(head->tokens);
	free(head->path);
	free(head->tokens_id);
	free(head);
	head = NULL;
}

void	free_args(t_args **root)
{
	t_args	*curr;
	t_args	*aux;

	curr = *root;
	while (curr)
	{
		aux = curr;
		curr = curr->next;
		free_arr(aux->args);
		free(aux->path);
		free(aux);
	}
	*root = NULL;
}

void	free_redirects(t_redirect **root)
{
	t_redirect	*curr;
	t_redirect	*aux;

	curr = *root;
	while (curr)
	{
		aux = curr;
		curr = curr->next;
		free_arr(aux->tokens);
		free(aux->tokens_id);
		free(aux);
	}
	*root = NULL;
}

void	free_tokens(t_token **root)
{
	t_token	*curr;
	t_token	*aux;

	curr = *root;
	while (curr)
	{
		aux = curr;
		curr = curr->next;
		free(aux->token);
		free(aux);
	}
	*root = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr && arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_envp(t_envp *head)
{
	t_envp	*current;
	t_envp	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	head = NULL;
}

void	free_struct(t_command *head)
{
	t_command	*current;
	t_command	*tmp;

	current = head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free_arr(tmp->args);
		free(tmp->path);
		free_prompt2(tmp->prompt);
		free(tmp);
	}
	head = NULL;
	free(head);
}
