/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:03:08 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:44:38 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_full_str(t_token *head)
{
	t_token	*cpy;

	cpy = head;
	while (cpy)
	{
		if (cpy->type == WORD)
		{
			cpy = ft_part_to_str(cpy->part_str, &cpy);
		}
		cpy = cpy->next;
	}
	return (NULL);
}

t_token	*ft_part_to_str(t_part *head_part, t_token **current_token)
{
	t_part	*cpy;
	char	*final_str;

	final_str = NULL;
	if (!current_token)
		return (NULL);
	cpy = head_part;
	if (head_part->next)
	{
		final_str = ft_strdup("");
		while (cpy)
		{
			if (cpy->quote_type == SP_QUOTED)
				final_str = ft_strjoin_free(final_str, ft_strdup(cpy->str));
			else if (cpy->quote_type == DB_QUOTED)
				final_str = ft_strjoin_free(final_str, ft_strdup(cpy->str));
			else if (cpy->quote_type == NON_QUOTED)
				final_str = ft_strjoin_free(final_str, ft_strdup(cpy->str));
			cpy = cpy->next;
		}
		(*current_token)->str_final = final_str;
	}
	else
		((*current_token)->str_final = ft_strdup(head_part->str));
	return (*current_token);
}

char	*expander(char *str)
{
	char	*temp;

	if (str[0] == '$')
	{
		temp = getenv(&str[1]);
		if (!temp)
			return (ft_strdup(str));
		else
			return (ft_strdup(temp));
	}
	return (ft_strdup(str));
}

t_token	*add_new_token(t_token *current_token, t_token *new_token)
{
	t_token	*cpy;
	t_token	*buffer;

	cpy = current_token;
	buffer = cpy->next;
	cpy->next = new_token;
	new_token->next = buffer;
	return (new_token->next);
}

void	ft_free(char **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}
