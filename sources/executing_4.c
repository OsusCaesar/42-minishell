/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:06:07 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 15:23:13 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_file_type(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (-1);
	if (S_ISDIR(st.st_mode))
		return (1);
	if (S_ISREG(st.st_mode))
		return (0);
	return (2);
}

int	check_command_path(char *path)
{
	if (get_file_type(path) == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (126);
	}
	if (get_file_type(path) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (126);
	}
	return (0);
}

char	*get_executable(char **args, char **paths)
{
	int		i;
	char	*slash;
	char	*path;

	if (!paths || ft_strchr(args[0], '/'))
	{
		i = check_command_path(args[0]);
		if (i)
			exit(i);
		return (args[0]);
	}
	i = -1;
	while (args[0][0] && paths[++i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slash, args[0]);
		free(slash);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], 2);
	free_strtab(paths);
	return (ft_putendl_fd(": command not found", STDERR_FILENO), NULL);
}

void	execute(t_cmd *cmd, t_environment *env, t_fds *fds)
{
	char	**paths;
	char	**envp;
	char	*exec;

	if (is_builtin(cmd))
		exit(exec_builtin(cmd, env, fds));
	envp = env_to_char(env);
	ft_free_env(&env);
	paths = get_paths(envp);
	exec = get_executable(cmd->argv, paths);
	if (!exec)
	{
		free_strtab(envp);
		ft_free_pipeline(&fds->pipeline);
		exit(127);
	}
	cmd->argv[0] = exec;
	if (execve(cmd->argv[0], cmd->argv, envp))
	{
		perror("minishell: execve");
		free_strtab(envp);
		free_strtab(paths);
		ft_free_pipeline(&fds->pipeline);
		exit(errno);
	}
}

// Forks, redirects the STD_IN and STD_OUT and calls the execute fct
int	exec_fork(t_cmd *cmd, t_environment *env, t_fds *fds, int *pids)
{
	int		pid;
	t_redir	*redir;

	pid = fork();
	if (pid < 0)
		ft_putendl_fd("Error while fork.", STDERR_FILENO);
	if (pid == 0)
	{
		setup_signals_child();
		if_free(pids);
		redir = cmd->redir;
		while (redir)
		{
			set_redir(redir, fds);
			redir = redir->next;
		}
		close(fds->pipefd[0]);
		if (fds->redir_out)
			dup2(fds->pipefd[1], STDOUT_FILENO);
		if (fds->redir_in)
			dup2(fds->last_out, STDIN_FILENO);
		close_pipe(fds->last_out, fds->pipefd[1]);
		execute(cmd, env, fds);
	}
	return (pid);
}
