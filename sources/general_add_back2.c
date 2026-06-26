/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_add_back2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:45:33 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/08 17:13:27 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_part	*part_add_back(t_part **head, t_part *new)
{
	t_part	*cpy;

	if (!new)
		return (NULL);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (new);
	}
	cpy = *head;
	while (cpy->next)
	{
		cpy = cpy->next;
	}
	cpy->next = new;
	return (new);
}

t_environment	*env_add_back(t_environment **head, t_environment *new)
{
	t_environment	*cpy;

	if (!new)
		return (NULL);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		(*head)->prev = NULL;
		return (new);
	}
	cpy = *head;
	while (cpy->next)
	{
		cpy = cpy->next;
	}
	new->prev = cpy;
	cpy->next = new;
	return (new);
}
