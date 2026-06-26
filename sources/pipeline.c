/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:55:48 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:30:46 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*ft_token_to_cmd(t_token *head_token)
{
	t_token		*cpy_token;
	t_pipeline	*new_pipeline;
	t_pipeline	*head_pipeline;
	t_cmd		*new_command;

	if (!head_token)
		return (NULL);
	cpy_token = head_token;
	new_pipeline = NULL;
	head_pipeline = NULL;
	new_command = NULL;
	if (token_loop(cpy_token, &new_pipeline, &head_pipeline, &new_command))
		return (ft_free_pipeline(&new_pipeline), ft_free_cmd(&new_command),
			NULL);
	if (new_command)
		cmd_add_back(&new_pipeline->command, new_command);
	if (new_pipeline)
		pipeline_add_back(&head_pipeline, new_pipeline);
	return (head_pipeline);
}

void	ft_error_near_2(t_enum_token type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	ft_putendl_fd((char *)token_type_to_charset(type), STDERR_FILENO);
	g_exit_status = 2;
}

int	is_valid_prev_prev(t_token *tkn)
{
	if (tkn->prev && tkn->prev->prev && tkn->prev->type == PARENTHESIS
		&& tkn->prev->prev->type == WORD)
		return (1);
	return (0);
}

int	ft_hdl_redir(t_token **tkn, t_cmd **n_cmd)
{
	ft_add_redir((*n_cmd), (*tkn)->type);
	if ((*tkn)->prev->type == (*tkn)->type)
		return (ft_error_near_2((*tkn)->type), 1);
	if ((*tkn)->next && (*tkn)->next->type == WORD)
	{
		(*tkn) = (*tkn)->next;
		add_back_filename(&(*n_cmd)->redir, ft_strdup((*tkn)->str_final));
	}
	else if (!(*tkn)->next)
	{
		g_exit_status = 2;
		return (ft_putendl_fd(ERREUR_TKN_NL, STDERR_FILENO), 1);
	}
	else if ((*tkn)->next->type != WORD)
		return (ft_error_near_2((*tkn)->next->type), 1);
	return (0);
}

int	ft_hdl_pipe(t_token **tkn, t_pipeline **new_pipeline, t_cmd **n_cmd)
{
	if (!(*tkn)->prev)
		return (ft_error_near_2((*tkn)->type), 1);
	else if ((*tkn)->prev->prev && (*tkn)->prev->type == PARENTHESIS
		&& (*tkn)->prev->prev->type == WORD)
		n_cmd_add_null(new_pipeline, n_cmd);
	else if ((*tkn)->prev && (*tkn)->prev->type != WORD)
		return (ft_error_near_2((*tkn)->type), 1);
	else
		n_cmd_add_null(new_pipeline, n_cmd);
	return (0);
}
