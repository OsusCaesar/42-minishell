/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:26:29 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:43:05 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*init_pipeline(void)
{
	t_pipeline	*new_pipeline;

	new_pipeline = malloc(sizeof(t_pipeline));
	new_pipeline->separator = 0;
	new_pipeline->next = NULL;
	new_pipeline->command = NULL;
	new_pipeline->error = NULL;
	new_pipeline->parenthesis = 0;
	return (new_pipeline);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	if (!new_command)
		return (NULL);
	new_command->argv = NULL;
	new_command->next = NULL;
	new_command->redir = NULL;
	return (new_command);
}

const char	*token_type_to_charset(t_enum_token type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("`|'");
	else if (type == REDIR_IN)
		return ("`<'");
	else if (type == REDIR_OUT)
		return ("`>'");
	else if (type == REDIR_APPEND)
		return ("`>>'");
	else if (type == HEREDOC)
		return ("`<<'");
	else if (type == EOL)
		return ("`EOL'");
	else if (type == ERROR)
		return ("`ERROR");
	else if (type == PIPES)
		return ("`||'");
	else if (type == AND)
		return ("`&'");
	else if (type == ANDS)
		return ("`&&'");
	else if (type == PARENTHESIS)
		return ("( )");
	return ("UNKNOWN");
}
