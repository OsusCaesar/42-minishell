/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:45 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 16:25:16 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*creat_token_list(char *line, t_token *head)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (is_parenthesis(line[i]))
			new_token_parenthesis(&head, &line[i]);
		else if (is_one_token(line[i], line[i + 1]))
		{
			new_token(&head, &line[i], 1);
			if (line[i] == REDIR_OUT_VAL
				&& (line[i + 1] == PIPE_VAL || line[i + 1] == AND_VAL))
				i++;
		}
		else if (is_db_token(line[i], line[i + 1]))
			new_token(&head, &line[i++], 2);
		else if (is_word_limit(line[i]))
		{
			new_word_token(&head, line, &i);
			i--;
		}
		i++;
	}
	return (head);
}

t_token	*analyse_str(char **line)
{
	t_token	*head;

	head = NULL;
	head = malloc(sizeof(t_token));
	if (!head)
		return (ft_free(line), NULL);
	head = init_token_type(&head, 10, 0);
	if (!head)
		return (ft_free(line), NULL);
	head->next = NULL;
	head->str_final = NULL;
	head = creat_token_list(*line, head);
	if (is_valid_parentheses(head))
	{
		ft_free_token(&head);
		g_exit_status = 0;
		return (NULL);
	}
	return (head);
}

char	*new_quote_part(char *str, int *i)
{
	char	quote;
	char	*word;

	quote = str[(*i)];
	(*i)++;
	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (str[(*i)] && str[(*i)] != quote)
	{
		str_cat_plus(&word, str[(*i)]);
		if (!word)
			return (NULL);
		(*i)++;
	}
	if (str[(*i)] == '\0')
		(printf("error quote\n"), exit(1));
	(*i)++;
	return (word);
}

int	quote_val_to_enum(char c)
{
	if (c == DB_QUOTE_VAL)
		return (DB_QUOTED);
	if (c == QUOTE_VAL)
		return (SP_QUOTED);
	return (0);
}

int	is_valid_parentheses(t_token *head)
{
	t_token	*cpy_token;
	int		parenthesis;

	cpy_token = head;
	parenthesis = 0;
	while (cpy_token)
	{
		if (cpy_token->part_str && cpy_token->part_str->quote_type == NON_QUOTED
			&& cpy_token->part_str->str[0] == '(')
			parenthesis++;
		else if (cpy_token->part_str
			&& cpy_token->part_str->quote_type == NON_QUOTED
			&& cpy_token->part_str->str[0] == ')')
			parenthesis--;
		if (parenthesis < 0)
			return (1);
		cpy_token = cpy_token->next;
	}
	if (parenthesis)
	{
		printf("error parentheses\n");
		return (1);
	}
	return (0);
}
