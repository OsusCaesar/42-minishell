/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:48:07 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 15:42:13 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# define ERREUR_TKN_NL "minishell: syntax error near unexpected token `newline'"
# include "environment.h"
# include "minishell.h"
# include "token.h"

typedef struct s_redir
{
	t_enum_token		type_redir;
	char				*filename;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				**argv;
	t_redir				*redir;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_pipeline
{
	t_cmd				*command;
	t_enum_token		separator;
	int					parenthesis;
	struct s_pipeline	*next;
	struct s_pipeline	*success;
	struct s_pipeline	*error;
}						t_pipeline;

// PIPELINE
t_pipeline				*ft_token_to_cmd(t_token *head);
void					ft_error_near_2(t_enum_token type);
int						is_valid_prev_prev(t_token *tkn);
int						ft_hdl_redir(t_token **tkn, t_cmd **n_cmd);
int						ft_hdl_pipe(t_token **tkn, t_pipeline **new_pipeline,
							t_cmd **n_cmd);

// PIPELINE 2
t_pipeline				*ft_find_next_ands(t_pipeline *current);
void					set_next_branch(t_pipeline *pipeline);
t_pipeline				*pipeline_to_tree(t_pipeline **head);
t_pipeline				*ft_find_next_pipes(t_pipeline *current);
void					separator_to_cmd(t_pipeline **head_pipeline,
							t_pipeline **new_pipeline, t_cmd **new_command,
							t_token *cpy_token);

// PIPELINE 3
t_redir					*ft_add_redir(t_cmd *new_command, t_enum_token type);
void					count_parenthesis(char *str, t_pipeline *new_pipeline);
int						token_loop(t_token *cpy_token,
							t_pipeline **new_pipeline,
							t_pipeline **head_pipeline, t_cmd **new_command);
void					n_cmd_add_null(t_pipeline **new_pipeline,
							t_cmd **n_cmd);

// PIPELINE INIT
t_pipeline				*init_pipeline(void);
t_cmd					*init_cmd(void);
const char				*token_type_to_charset(t_enum_token type);

// PIPELINE FREE
void					ft_free_pipeline(t_pipeline **head);
void					ft_free_cmd(t_cmd **head);
void					ft_free_redir(t_redir **head);

// GENERAL ADD BACK
t_cmd					*cmd_add_back(t_cmd **head, t_cmd *new);
t_pipeline				*pipeline_add_back(t_pipeline **head, t_pipeline *new);
t_redir					*add_back_filename(t_redir **head, char *filename);
t_redir					*ft_redir_add_back(t_redir **head, t_redir *new);

// GENERAL UTILS
char					**cat_argv(char **argv, char *str_final);

// GENERAL IS ASCII 2
t_enum_token			is_pipeline_separator(t_enum_token type);
int						is_redir(t_enum_token type);

#endif
