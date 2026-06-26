/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:14:15 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 15:39:18 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_add_back(t_token **head, t_token *new)
{
	t_token	*cpy;

	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
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
	new->prev = cpy;
	return (new);
}

t_token	*init_token_type(t_token **new, int type, int init_part)
{
	if (!(*new))
		return (NULL);
	(*new)->type = type;
	(*new)->prev = NULL;
	(*new)->str_final = NULL;
	if (init_part)
	{
		(*new)->part_str = malloc(sizeof(t_part));
		if (!(*new)->part_str)
		{
			free((*new));
			new = NULL;
			return (NULL);
		}
		(*new)->part_str->quote_type = 0;
		(*new)->part_str->next = NULL;
	}
	else
		(*new)->part_str = NULL;
	return (*new);
}

// Ajoute a la fin de head le token (size=1) ou double token (size=2)
// composé de |, >, < ou &
t_token	*new_token(t_token **head, char *str, int size_token)
{
	t_token	*new;

	new = NULL;
	new = malloc(sizeof(t_token));
	init_token_type(&new, 10, 1);
	if (!new)
		return (NULL);
	new->str_final = NULL;
	new->prev = NULL;
	if (size_token == 2)
	{
		new->type = is_db_token(str[0], str[1]);
		new->part_str->str = ft_strndup(str, 2);
		if (!new->part_str->str)
			return (NULL);
	}
	else if (size_token == 1)
	{
		new->type = is_one_token(str[0], str[1]);
		new->part_str->str = ft_strndup(str, 1);
		if (!new->part_str->str)
			return (NULL);
	}
	token_add_back(head, new);
	return (new);
}

t_token	*new_token_parenthesis(t_token **head, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = PARENTHESIS;
	new->prev = NULL;
	new->str_final = NULL;
	new->part_str = malloc(sizeof(t_part));
	if (!new->part_str)
		return (NULL);
	new->part_str->quote_type = 0;
	new->part_str->next = NULL;
	new->part_str->str = ft_strndup(str, 1);
	if (!new->part_str->str)
		return (NULL);
	token_add_back(head, new);
	return (new);
}
