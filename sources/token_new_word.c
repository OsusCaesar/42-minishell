/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:50:52 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 17:49:11 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ajoute a head le token "mot" lu dans str à l'indice i
// incrémente i jusqu'à la fin du token
t_token	*new_word_token(t_token **head_token, char *str, int *i)
{
	char	*word;
	t_token	*new_token;
	t_part	*head_part;

	head_part = NULL;
	while (str[(*i)] && !is_meta_char(str[(*i)]) && !is_parenthesis(str[(*i)]))
	{
		word = ft_strdup("");
		if (!word)
			return (NULL);
		if (is_quote(str[(*i)]))
		{
			if (quote_word(&word, str, i, &head_part))
				return (NULL);
		}
		else
		{
			if (!cat_until_unvalid_char(i, str, &word)
				|| !creat_and_add_part(&head_part, word))
				return (NULL);
		}
	}
	new_token = creat_and_add_token(head_token, head_part);
	return (new_token);
}

// allocate a t_part with the word in itself until it_s the same quote again
int	quote_word(char **word, char *str, int *i, t_part **head_part)
{
	t_part	*new_part;
	char	quote;

	quote = str[(*i)];
	if ((*word)[0] == '\0')
		ft_free_str(word);
	*word = new_quote_part(str, i);
	if (!*word)
		return (1);
	new_part = malloc(sizeof(t_part));
	if (!new_part)
		return (free(*word), 1);
	new_part->str = *word;
	new_part->quote_type = quote_val_to_enum(quote);
	new_part->next = NULL;
	part_add_back(head_part, new_part);
	return (0);
}

// alloc new token,get the t_Part to associate
// with and add back to the token list
t_token	*creat_and_add_token(t_token **head, t_part *head_part)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->part_str = head_part;
	new_token->type = WORD;
	new_token->next = NULL;
	new_token->prev = NULL;
	new_token->str_final = NULL;
	token_add_back(head, new_token);
	return (new_token);
}

t_part	*creat_and_add_part(t_part **head_part, char *word)
{
	t_part	*new_part;

	new_part = malloc(sizeof(t_part));
	if (!new_part)
		return (NULL);
	new_part->str = word;
	new_part->quote_type = NON_QUOTED;
	part_add_back(head_part, new_part);
	return (new_part);
}

char	*cat_until_unvalid_char(int *i, char *str, char **word)
{
	while (str[(*i)] && (!is_meta_char(str[(*i)]) && !is_quote(str[(*i)])
			&& !is_parenthesis(str[(*i)])))
	{
		str_cat_plus(word, str[(*i)]);
		if (!*word)
			return (0);
		(*i)++;
	}
	return (*word);
}

// t_token	*new_word_token(t_token **head, char *str, int *i)
// {
// 	char	*word;
// 	// char	quote;
// 	t_token	*new_token;
// 	t_part	*head_part;
// 	t_part	*new_part;

// 	head_part = NULL;
// 	while (str[(*i)] && !is_meta_char(str[(*i)])
// && !is_parenthesis(str[(*i)]))
// 	{
// 		word = ft_strdup("");
// 		if (!word)
// 			return (NULL);
// 		if (is_quote(str[(*i)]))
// 		{
// 			// quote = str[(*i)];
// 			// if (word[0] == '\0')
// 			// 	ft_free_str(&word);
// 			// word = new_quote_part(str, i);
// 			// if (!word)
// 			// 	return (NULL);
// 			// new_part = malloc(sizeof(t_part));
// 			// if (!new_part)
// 			// 	return (NULL);
// 			// new_part->str = word;
// 			// new_part->quote_type = quote_val_to_enum(quote);
// 			// new_part->next = NULL;
// 			// part_add_back(&head_part, new_part);
// 		}
// 		else
// 		{
// 			while (str[(*i)] && (!is_meta_char(str[(*i)])
// 					&& !is_quote(str[(*i)]) && !is_parenthesis(str[(*i)])))
// 			{
// 				str_cat_plus(&word, str[(*i)]);
// 				if (!word)
// 					return (0);
// 				(*i)++;
// 			}
// 			new_part = malloc(sizeof(t_part));
// 			if (!new_part)
// 				return (NULL);
// 			new_part->str = word;
// 			new_part->quote_type = NON_QUOTED;
// 			part_add_back(&head_part, new_part);
// 		}
// 	}
// 	new_token = malloc(sizeof(t_token));
// 	if (!new_token)
// 		return (NULL);
// 	new_token->part_str = head_part;
// 	new_token->type = WORD;
// 	new_token->next = NULL;
// 	token_add_back(head, new_token);
// 	return (new_token);
// }