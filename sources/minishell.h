/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:06:21 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 14:58:20 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NO_ARG "minishell: no arguments expected."

# include "libft.h"
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto,
					// tputs
# include <dirent.h> // opendir, readdir, closedir
# include <errno.h>
# include <fcntl.h>             // open, unlink
# include <readline/history.h>  // add_history
# include <readline/readline.h> // readline, rl_clear_history, rl_on_new_line,
								// rl_replace_line, rl_redisplay
# include <signal.h>            // signal, sigaction, sigemptyset, sigaddset,
								// kill
# include <stdio.h>             // printf, perror
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <sys/ioctl.h>         // ioctl
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // opendir, wait, waitpid, wait3, wait4
# include <sys/wait.h>          // wait, waitpid, wait3, wait4
# include <term.h>              // termcap functions (idem au-dessus)
# include <termios.h>           // tcgetattr, tcsetattr
# include <unistd.h>            // write, access, read, close, fork, chdir, dup,
								// dup2, execve, isatty, ttyname, ttyslot
# include "environment.h"
# include "executing.h"
# include "expand.h"
# include "pipeline.h"
# include "token.h"

extern int		g_exit_status;

// MINISHELL__C
int				ft_minishell(char **input, t_environment *env);
int				is_quote(char c);

// SIGNAL__C
void			sigint_handler(int sig);
void			setup_signals_child(void);
void			setup_signals_main(void);

// GENERAL_IS_ASCII
t_enum_token	is_one_token(char c, char second_c);
int				is_space(char c);
int				is_meta_char(char c);

// GENERAL_IS_ASCII_2
t_enum_token	is_db_token(char c, char second_c);
int				is_word_limit(char c);
int				is_parenthesis(char c);

// GENERAL ADD BACK 2
t_part			*part_add_back(t_part **head, t_part *new);

// GENERAL UTILS
char			*str_cat_plus(char **str, char c);
char			*ft_strndup(const char *s, int size);
char			*ft_strjoin_free(char *s1, char *s2);

// GENERAL FREE
char			*ft_free_str(char **str);
t_token			*ft_free_token(t_token **head);
t_part			*ft_free_part(t_part **head);

#endif