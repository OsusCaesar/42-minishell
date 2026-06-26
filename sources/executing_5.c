/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:04:53 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 13:30:39 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executes only the pipeline "pipeline"
int	execute_pipe(t_pipeline *pipeline, t_environment *env)
{
	t_fds	fds;
	t_cmd	*cmd;
	pid_t	*pids;
	int		i;

	cmd = pipeline->command;
	if (ft_cmd_size(cmd) == 1 && is_builtin(cmd))
		return (exec_builtin_alone(cmd, env));
	pids = malloc(sizeof(pid_t) * ft_cmd_size(cmd));
	init_fds(&fds, ft_cmd_size(cmd), pipeline);
	i = 0;
	while (cmd->next)
	{
		pids[i++] = exec_fork(cmd, env, &fds, pids);
		close_pipe(fds.last_out, fds.pipefd[1]);
		fds.last_out = fds.pipefd[0];
		fds.redir_in = 1;
		pipe(fds.pipefd);
		cmd = cmd->next;
	}
	fds.redir_out = 0;
	pids[i++] = exec_fork(cmd, env, &fds, pids);
	close(fds.last_out);
	close_pipe(fds.pipefd[0], fds.pipefd[1]);
	return (wait_cmds(pids, i));
}

// Executes the pipelines of the chained list "pipeline"
void	execute_pipeline(t_pipeline *pipeline, t_environment *env)
{
	t_pipeline	*curr_pl;
	int			error;

	curr_pl = pipeline;
	while (curr_pl)
	{
		error = execute_pipe(curr_pl, env);
		g_exit_status = error;
		if (error)
			curr_pl = curr_pl->error;
		else
			curr_pl = curr_pl->success;
	}
}

char	**get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

int	wait_cmds(pid_t *pids, int nb_cmds)
{
	int	status;
	int	i;

	i = 0;
	while (i < nb_cmds)
	{
		waitpid(pids[i++], &status, 0);
	}
	if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
	{
		g_exit_status = WEXITSTATUS(status);
	}
	free(pids);
	return (g_exit_status);
}
