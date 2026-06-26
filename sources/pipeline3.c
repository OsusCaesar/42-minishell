/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:55:48 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 12:31:58 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_hdl_separator(t_token **tkn, t_pipeline **head_pipeline,
		t_pipeline **new_pipeline, t_cmd **n_cmd)
{
	if (!(*tkn)->prev)
		return (ft_error_near_2((*tkn)->next->type), 1);
	else if (is_valid_prev_prev((*tkn)))
		separator_to_cmd(head_pipeline, new_pipeline, n_cmd, (*tkn));
	else if ((*tkn)->prev && (*tkn)->prev->type != WORD)
		return (ft_error_near_2((*tkn)->type), 1);
	separator_to_cmd(head_pipeline, new_pipeline, n_cmd, (*tkn));
	return (0);
}

int	token_loop(t_token *tkn, t_pipeline **new_pipeline,
		t_pipeline **head_pipeline, t_cmd **n_cmd)
{
	while (tkn)
	{
		if (!*new_pipeline)
			(*new_pipeline) = init_pipeline();
		if (!*n_cmd)
			*n_cmd = init_cmd();
		if (tkn->type == WORD)
			(*n_cmd)->argv = cat_argv((*n_cmd)->argv, tkn->str_final);
		else if (tkn->type == PIPE && ft_hdl_pipe(&tkn, new_pipeline, n_cmd))
			return (1);
		else if (is_redir(tkn->type) && (*n_cmd) && ft_hdl_redir(&tkn, n_cmd))
			return (1);
		else if (tkn->type == PARENTHESIS)
			count_parenthesis(tkn->part_str->str, (*new_pipeline));
		else if (tkn->type == AND)
			return (ft_error_near_2(tkn->type), 1);
		else if (is_pipeline_separator(tkn->type) && ft_hdl_separator(&tkn,
				head_pipeline, new_pipeline, n_cmd))
			return (1);
		tkn = tkn->next;
	}
	return (0);
}

void	n_cmd_add_null(t_pipeline **new_pipeline, t_cmd **n_cmd)
{
	cmd_add_back(&(*new_pipeline)->command, (*n_cmd));
	*n_cmd = NULL;
}

void	count_parenthesis(char *str, t_pipeline *new_pipeline)
{
	if (str[0] == ')')
		new_pipeline->parenthesis--;
	else if (str[0] == '(')
		new_pipeline->parenthesis++;
}

t_redir	*ft_add_redir(t_cmd *new_command, t_enum_token type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type_redir = type;
	new_redir->filename = NULL;
	new_redir->next = NULL;
	ft_redir_add_back(&new_command->redir, new_redir);
	return (new_redir);
}
