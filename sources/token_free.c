/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:27:31 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:40:18 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_full_token(t_token **head)
{
	t_token	*cpy;
	t_token	*buf;

	if (!*head || !head)
		return ;
	cpy = *head;
	while (cpy)
	{
		buf = cpy->next;
		if (cpy->part_str)
			ft_free_t_part(&cpy->part_str);
		free(cpy);
		cpy = buf;
	}
	*head = NULL;
}

void	ft_free_t_part(t_part **head)
{
	t_part	*buf;
	t_part	*cpy;

	if (!*head || !head)
		return ;
	cpy = *head;
	while (cpy)
	{
		buf = cpy->next;
		ft_free_str(&cpy->str);
		free(cpy);
		cpy = buf;
	}
	*head = NULL;
}
