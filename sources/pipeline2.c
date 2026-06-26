/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:05:39 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 12:31:52 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_next_branch(t_pipeline *pipeline)
{
	if (pipeline->separator == ANDS)
	{
		if (pipeline->next->command)
			pipeline->success = pipeline->next;
		else
			pipeline->success = NULL;
		pipeline->error = ft_find_next_pipes(pipeline);
	}
	else if (pipeline->separator == PIPES)
	{
		pipeline->success = ft_find_next_ands(pipeline);
		if (pipeline->next->command)
			pipeline->error = pipeline->next;
		else
			pipeline->error = NULL;
	}
}

t_pipeline	*pipeline_to_tree(t_pipeline **head)
{
	t_pipeline	*current;

	current = *head;
	while (current)
	{
		if (current->separator == ANDS || current->separator == PIPES)
			set_next_branch(current);
		else
		{
			current->success = NULL;
			current->error = NULL;
		}
		current = current->next;
	}
	return (*head);
}

t_pipeline	*ft_find_next_ands(t_pipeline *current)
{
	t_pipeline	*cpy;
	int			parentheses;

	parentheses = 0;
	cpy = current;
	while (cpy)
	{
		parentheses += cpy->parenthesis;
		if (!parentheses && cpy->separator == ANDS && cpy->next->command)
			return (cpy->next);
		cpy = cpy->next;
	}
	return (NULL);
}

t_pipeline	*ft_find_next_pipes(t_pipeline *current)
{
	t_pipeline	*cpy;
	int			parentheses;

	parentheses = 0;
	cpy = current;
	while (cpy)
	{
		parentheses += cpy->parenthesis;
		if (cpy->separator == PIPES && parentheses == 0 && cpy->next->command)
			return ((cpy->next));
		cpy = cpy->next;
	}
	return (NULL);
}

void	separator_to_cmd(t_pipeline **head_pipeline, t_pipeline **new_pipeline,
		t_cmd **new_command, t_token *cpy_token)
{
	if ((*new_command))
	{
		cmd_add_back(&(*new_pipeline)->command, (*new_command));
		*new_command = NULL;
	}
	(*new_pipeline)->separator = is_pipeline_separator(cpy_token->type);
	pipeline_add_back(head_pipeline, (*new_pipeline));
	*new_pipeline = init_pipeline();
}
