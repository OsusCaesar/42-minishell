/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:04:53 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 13:38:20 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	*name;

	if (!cmd->argv)
		return (1);
	name = cmd->argv[0];
	if (!ft_strncmp(name, "echo", 5) || !ft_strncmp(name, "cd", 3)
		|| !ft_strncmp(name, "pwd", 4) || !ft_strncmp(name, "export", 7)
		|| !ft_strncmp(name, "unset", 6) || !ft_strncmp(name, "env", 4)
		|| !ft_strncmp(name, "exit", 5))
		return (1);
	return (0);
}

int	set_redirs_builtin(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir;
	if (!redir)
		return (0);
	while (redir)
	{
		if (check_redir(redir, NULL))
			return (-1);
		if (redir->type_redir == REDIR_IN)
			dup2(set_input_file(redir->filename), STDIN_FILENO);
		if (redir->type_redir == HEREDOC)
			dup2(set_input_heredoc(redir->filename), STDIN_FILENO);
		if (redir->type_redir == REDIR_OUT || redir->type_redir == REDIR_APPEND)
		{
			fd = set_output(redir->filename, redir->type_redir);
			if (fd < 0)
				return (-1);
			dup2(fd, STDOUT_FILENO);
		}
		redir = redir->next;
	}
	return (0);
}

void	std_save(int save[2], int state)
{
	if (state)
	{
		save[0] = dup(STDIN_FILENO);
		save[1] = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(save[0], STDIN_FILENO);
		dup2(save[1], STDOUT_FILENO);
		close_pipe(save[0], save[1]);
	}
}

// executes the builtin cmd with redirs
int	exec_builtin_alone(t_cmd *cmd, t_environment *env)
{
	int		error;
	int		save[2];

	error = 0;
	std_save(save, 1);
	if (set_redirs_builtin(cmd) == -1)
		return (1);
	if (!cmd->argv)
		return (std_save(save, 0), 0);
	if (!ft_strncmp(cmd->argv[0], "echo", 4))
		error = ft_echo(cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "cd", 2))
		error = ft_cd(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 3))
		error = ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "export", 6))
		error = ft_export(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "unset", 5))
		error = ft_unset(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "env", 3))
		error = ft_env(cmd->argv, env);
	else if (!ft_strncmp(cmd->argv[0], "exit", 4))
		error = ft_exit(cmd->argv, &env);
	std_save(save, 0);
	return (error);
}

// executes the builtin cmd
int	exec_builtin(t_cmd *cmd, t_environment *env, t_fds *fds)
{
	int		error;
	char	*name;

	error = 0;
	if (!cmd->argv)
		return (0);
	name = cmd->argv[0];
	if (!ft_strncmp(name, "echo", 4))
		error = ft_echo(cmd->argv);
	if (!ft_strncmp(name, "cd", 2))
		error = ft_cd(cmd->argv, env);
	if (!ft_strncmp(name, "pwd", 3))
		error = ft_pwd();
	if (!ft_strncmp(name, "export", 6))
		error = ft_export(cmd->argv, env);
	if (!ft_strncmp(name, "unset", 5))
		error = ft_unset(cmd->argv, env);
	if (!ft_strncmp(name, "env", 3))
		error = ft_env(cmd->argv, env);
	if (!ft_strncmp(name, "exit", 4))
		error = ft_exit(cmd->argv, &env);
	ft_free_env(&env);
	ft_free_pipeline(&fds->pipeline);
	return (error);
}
