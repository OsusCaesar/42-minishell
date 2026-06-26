/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:33:10 by jferrand          #+#    #+#             */
/*   Updated: 2025/10/13 15:29:25 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_fds *fds, int pipe_size, t_pipeline *pipeline)
{
	int	ghost_pipe[2];

	fds->pipeline = pipeline;
	pipe(fds->pipefd);
	fds->redir_in = 0;
	if (pipe_size == 1)
		fds->redir_out = 0;
	else
		fds->redir_out = 1;
	pipe(ghost_pipe);
	fds->last_out = ghost_pipe[0];
	close(ghost_pipe[1]);
}

void	close_pipe(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

// Verifies the input file rights and existence and returns the input fd
int	set_input_file(char *filename)
{
	int	input;

	if (access(filename, F_OK) != 0)
	{
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
		return (-1);
	}
	if (access(filename, R_OK) != 0)
	{
		ft_putendl_fd("Can't read input file.", STDERR_FILENO);
		return (-1);
	}
	input = open(filename, O_RDONLY);
	if (input < 0)
	{
		ft_putendl_fd("Error while opening input file.", STDERR_FILENO);
		return (-1);
	}
	return (input);
}

// Reads the heredoc input and returns the input fd
int	set_input_heredoc(char *limiter)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			break ;
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

// Returns the output fd, verifying if the output file has the necessary rights
int	set_output(char *filename, int type)
{
	int	fd;

	if (type == REDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
	}
	return (fd);
}
