/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:28:48 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 15:45:09 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "environment.h"
# include "token.h"

// EXPAND_WILDCARD
char	*expand_wildcard(char *cmd, int *index);

// EXPAND_C
char	*ft_getenv(char *var_name, t_environment *env);
char	*str_replace(char *new, char *original, int start, int end);
void	ft_end_exp_env(char *var_name, char *var_content, char *cmd,
			int *index);
char	*expand_env(char *cmd, int *index, t_environment *env, int db_quote);
void	ft_end_exp_cmd(char *cmd, char **exp, t_environment *env,
			int env_or_wc);
char	*get_token_full_str(t_token *head);

// EXPAND_2_C
char	*expand_cmd(char *cmd, t_environment *env, int env_or_wc);

// EXPAND_3_C
char	*expander(char *str);
t_token	*add_new_token(t_token *head, t_token *new_token);
t_token	*ft_part_to_str(t_part *head_part, t_token **current_token);
void	ft_free(char **to_free);

#endif // !EXPAND_H