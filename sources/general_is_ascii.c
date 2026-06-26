/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_is_ascii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:53:36 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:40:40 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if ((c > 7 && c < 14) || c == 32)
		return (1);
	else
		return (0);
}

int	is_quote(char c)
{
	if (c == QUOTE_VAL)
		return (QUOTE_VAL);
	else if (c == DB_QUOTE_VAL)
		return (DB_QUOTE_VAL);
	else
		return (0);
}

int	is_meta_char(char c)
{
	if (c == PIPE_VAL)
		return (PIPE_VAL);
	else if (c == REDIR_IN_VAL)
		return (REDIR_IN_VAL);
	else if (c == REDIR_OUT_VAL)
		return (REDIR_OUT_VAL);
	else if (is_space(c))
		return (1);
	return (0);
}

// analyse les metchar pour savoir si ils sont seul ou double
t_enum_token	is_one_token(char c, char second_c)
{
	if (c == PIPE_VAL && c != second_c)
		return (PIPE);
	else if (c == REDIR_IN_VAL && c != second_c)
		return (REDIR_IN);
	else if (c == REDIR_OUT_VAL && c != second_c)
		return (REDIR_OUT);
	else if (c == AND_VAL && c != second_c)
		return (AND);
	else
		return (0);
}
