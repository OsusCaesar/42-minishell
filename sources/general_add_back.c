/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:26:43 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/08 21:01:27 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*pipeline_add_back(t_pipeline **head, t_pipeline *new)
{
	t_pipeline	*cpy;

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

t_redir	*add_back_filename(t_redir **head, char *filename)
{
	t_redir	*cpy;

	cpy = *head;
	while (cpy->next)
	{
		cpy = cpy->next;
	}
	cpy->filename = filename;
	return (cpy);
}

t_redir	*ft_redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*cpy;

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

t_cmd	*cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*cpy;

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
