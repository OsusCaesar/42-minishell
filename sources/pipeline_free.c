/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:01:42 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:39:55 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipeline(t_pipeline **head)
{
	t_pipeline	*cpy;
	t_pipeline	*buf;

	if (!head || !*head)
		return ;
	cpy = *head;
	while (cpy)
	{
		buf = cpy->next;
		if (cpy->command)
			ft_free_cmd(&cpy->command);
		free(cpy);
		cpy = buf;
	}
	*head = NULL;
}

void	ft_free_cmd(t_cmd **head)
{
	t_cmd	*buf;
	t_cmd	*cpy;

	if (!head || !*head)
		return ;
	cpy = *head;
	while (cpy)
	{
		buf = cpy->next;
		if (cpy->argv)
			free_strtab(cpy->argv);
		if (cpy->redir)
			ft_free_redir(&cpy->redir);
		free(cpy);
		cpy = buf;
	}
	*head = NULL;
}

void	ft_free_redir(t_redir **head)
{
	t_redir	*buf;
	t_redir	*cpy;

	if (!head || !*head)
		return ;
	cpy = *head;
	while (cpy)
	{
		buf = cpy->next;
		ft_free_str(&cpy->filename);
		free(cpy);
		cpy = buf;
	}
	*head = NULL;
}
