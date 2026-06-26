/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:56:46 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 14:38:31 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_environment
{
	char					*name;
	char					*content;
	struct s_environment	*next;
	struct s_environment	*prev;

}							t_environment;

// ENVIRONMENT
char						*ft_get_name(char *line);
char						*ft_get_content_env(char *line);
t_environment				*ft_cpy_env(char **env);
char						*ft_get_name_export(char *line);
int							ft_content_env_unvalid(char *line);

// ENVIRONMENT 2
char						*ft_get_str_env(t_environment *cpy);
char						**env_to_char(t_environment *env);

// ENVIRONMENT FREE
void						ft_print_db_char(char **env_char);
t_environment				*env_sort(t_environment *head);
void						ft_free_env(t_environment **head);

// GENERAL ADD BACK
t_environment				*env_add_back(t_environment **head,
								t_environment *new);

#endif
