/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:28:36 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 15:39:46 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define DB_QUOTE_VAL 34
# define DOLLAR_VAL 36
# define AND_VAL 38
# define QUOTE_VAL 39
# define REDIR_IN_VAL 60
# define REDIR_OUT_VAL 62
# define PIPE_VAL 124
# define WILDCARD_VAL 42
# define SEPARATOR 12400

# define ERROR_ALLOC 2

//# include "minishell.h"
# include "environment.h"

typedef enum e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	ANDS,
	REDIR_APPEND,
	HEREDOC,
	PIPES,
	EOL,
	AND,
	WILDCARD,
	ERROR,
	PARENTHESIS
}					t_enum_token;

typedef enum e_quote
{
	NON_QUOTED,
	SP_QUOTED,
	DB_QUOTED
}					t_quote;

typedef struct s_part
{
	t_quote			quote_type;
	char			*str;
	struct s_part	*next;
}					t_part;

typedef struct s_token
{
	t_enum_token	type;
	t_part			*part_str;
	char			*str_final;
	struct s_token	*next;
	struct s_token	*prev;

}					t_token;

// char				**ft_split_cmd(char *cmd);

// TOKEN_C
t_token				*analyse_str(char **line);
char				*new_quote_part(char *str, int *i);
int					quote_val_to_enum(char c);
int					is_valid_parentheses(t_token *head);
t_token				*creat_token_list(char *line, t_token *head);

// TOKEN_STRUCT
t_token				*new_token(t_token **head, char *str, int size_token);
t_token				*token_add_back(t_token **head, t_token *new);
t_token				*new_token_parenthesis(t_token **head, char *str);
t_token				*init_token_type(t_token **new, int type, int init_part);

// TOKEN_NEW_WORD
t_token				*new_word_token(t_token **head, char *str, int *i);
int					quote_word(char **word, char *str, int *i,
						t_part **head_part);
t_token				*creat_and_add_token(t_token **head, t_part *head_part);
char				*cat_until_unvalid_char(int *i, char *str, char **word);
t_part				*creat_and_add_part(t_part **head_part, char *word);

// void				ft_free_t_part(t_part **head);
// void				ft_free_full_token(t_token **head);

#endif
