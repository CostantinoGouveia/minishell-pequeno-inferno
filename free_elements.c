/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <cgouveia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:52:19 by cgouveia          #+#    #+#             */
/*   Updated: 2025/02/10 09:54:58 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
