/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:32:09 by jferrand          #+#    #+#             */
/*   Updated: 2025/10/13 15:38:52 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H
# include "pipeline.h"

typedef struct s_fds
{
	int			pipefd[2];
	int			last_out;
	int			redir_in;
	int			redir_out;
	t_pipeline	*pipeline;
}				t_fds;

// EXECUTING
void			init_fds(t_fds *fds, int pipe_size, t_pipeline *pipeline);
void			close_pipe(int fd1, int fd2);
int				set_input_file(char *filename);
int				set_input_heredoc(char *limiter);
int				set_output(char *filename, int is_append);

// EXECUTING 2
int				is_builtin(t_cmd *cmd);
int				exec_builtin(t_cmd *cmd, t_environment *env, t_fds *fds);
int				exec_builtin_alone(t_cmd *cmd, t_environment *env);

// EXECUTING 3
void			set_redir(t_redir *redir, t_fds *fds);
int				check_redir(t_redir *redir, t_fds *fds);
void			set_input(t_redir *redir, t_fds *fds);

// EXECUTING 4
int				exec_fork(t_cmd *cmd, t_environment *env, t_fds *fds,
					int *pids);
void			execute(t_cmd *cmd, t_environment *env, t_fds *fds);
int				exec_fork(t_cmd *cmd, t_environment *env, t_fds *fds,
					int *pids);
char			*get_executable(char **args, char **paths);

// EXECUTING 5
void			execute_pipeline(t_pipeline *pipeline, t_environment *env);
int				execute_pipe(t_pipeline *pipeline, t_environment *env);
int				wait_cmds(pid_t *pids, int nb_cmds);
char			**get_paths(char **env);

// BUILT-IN
int				ft_cd(char **argv, t_environment *env);
int				ft_cd_with_arg(char *arg);
int				ft_pwd(void);
int				ft_echo(char **argv);

// BUILT-IN 2
int				ft_export(char **argv, t_environment *env);

// BUILT-IN 3
int				ft_env(char **argv, t_environment *env);
int				ft_unset(char **argv, t_environment *env);
int				ft_exit(char **argv, t_environment **env);
int				is_atoi_valid(char *str);

// GENERAL UTILS
int				ft_cmd_size(t_cmd *cmd);

// GENERAL FREE
void			free_strtab(char **strs);
void			if_free(void *allocd);

#endif