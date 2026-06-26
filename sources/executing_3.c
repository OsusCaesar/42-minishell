/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:06:07 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 13:28:47 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_redir_error(char *filename, char *msg, t_fds *fds)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (filename)
		ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	if (fds)
	{
		close_pipe(fds->pipefd[0], fds->pipefd[1]);
		close(fds->last_out);
	}
	return (1);
}

int	check_file_permissions(t_redir *redir, t_fds *fds, struct stat *st)
{
	if (S_ISDIR(st->st_mode))
		return (print_redir_error(redir->filename, ": Is a directory", fds));
	if (!S_ISREG(st->st_mode))
		return (0);
	if (redir->type_redir == REDIR_IN && access(redir->filename, R_OK) != 0)
		return (print_redir_error(redir->filename, ": Permission denied", fds));
	if ((redir->type_redir == REDIR_OUT || redir->type_redir == REDIR_APPEND)
		&& access(redir->filename, W_OK) != 0)
		return (print_redir_error(redir->filename, ": Permission denied", fds));
	return (0);
}

// Checks if the redir is valid, if not throws an error and exits
int	check_redir(t_redir *redir, t_fds *fds)
{
	struct stat	st;

	if (redir->type_redir == HEREDOC)
		return (0);
	if (stat(redir->filename, &st) == -1)
	{
		if (redir->type_redir == REDIR_IN)
			return (print_redir_error(redir->filename,
					": No such file or directory", fds));
		return (0);
	}
	return (check_file_permissions(redir, fds, &st));
}

void	set_input(t_redir *redir, t_fds *fds)
{
	if (redir->type_redir == REDIR_IN)
	{
		close(fds->last_out);
		fds->last_out = set_input_file(redir->filename);
		fds->redir_in = 1;
	}
	if (redir->type_redir == HEREDOC)
	{
		close(fds->last_out);
		fds->last_out = set_input_heredoc(redir->filename);
		fds->redir_in = 1;
	}
}

// Sets the input and/or output with the redir
void	set_redir(t_redir *redir, t_fds *fds)
{
	if (check_redir(redir, fds))
		exit(1);
	if (redir->type_redir == REDIR_IN || redir->type_redir == HEREDOC)
		set_input(redir, fds);
	if (redir->type_redir == REDIR_OUT || redir->type_redir == REDIR_APPEND)
	{
		close(fds->pipefd[1]);
		fds->pipefd[1] = set_output(redir->filename, redir->type_redir);
		if (fds->pipefd[1] == -1)
			exit(1);
		fds->redir_out = 1;
	}
}
