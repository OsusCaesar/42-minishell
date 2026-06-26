/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_is_ascii_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:52:57 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:40:28 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// analyse les metchar pour savoir si ils sout double
t_enum_token	is_db_token(char c, char second_c)
{
	if (c == PIPE_VAL && c == second_c)
		return (PIPES);
	else if (c == REDIR_IN_VAL && c == second_c)
		return (HEREDOC);
	else if (c == REDIR_OUT_VAL && c == second_c)
		return (REDIR_APPEND);
	else if (c == AND_VAL && c == second_c)
		return (ANDS);
	else
		return (0);
}

t_enum_token	is_pipeline_separator(t_enum_token type)
{
	if (type == PIPES)
		return (PIPES);
	if (type == ANDS)
		return (ANDS);
	return (0);
}

int	is_redir(t_enum_token type)
{
	if (type == REDIR_IN)
		return ((int)REDIR_IN);
	if (type == HEREDOC)
		return ((int)HEREDOC);
	if (type == REDIR_OUT)
		return ((int)REDIR_OUT);
	if (type == REDIR_APPEND)
		return ((int)REDIR_APPEND);
	return (0);
}

int	is_parenthesis(char c)
{
	if (c == 40)
		return (40);
	if (c == 41)
		return (41);
	return (0);
}

int	is_word_limit(char c)
{
	if (!is_space(c) && (ft_isascii(c)))
		return (1);
	return (0);
}
