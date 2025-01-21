/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:17:00 by cgouveia          #+#    #+#             */
/*   Updated: 2024/05/22 12:21:48 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*novo;

	novo = malloc(sizeof(t_list));
	if (!novo)
		return (NULL);
	novo->content = content;
	novo->next = NULL;
	return (novo);
}
