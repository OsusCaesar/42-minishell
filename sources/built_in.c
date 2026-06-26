/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:30:13 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 12:50:09 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	i;

	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i = 1;
		while (argv[++i])
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (argv[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	else
	{
		i = 0;
		while (argv[++i])
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (argv[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}

int	ft_cd_with_arg(char	*arg)
{
	char	*cwd;

	if (!ft_strncmp(arg, "-", 2))
		return (ft_pwd());
	if (arg[0] == '-' && arg[1] == '-' && !arg[2])
		return (0);
	if (!ft_strncmp(arg, "-", 2))
		return (ft_pwd());
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(cwd + 1, arg, ft_strlen(cwd)))
		return (free(cwd), 0);
	free(cwd);
	if (chdir(arg))
		return (perror("minishell: cd"), 1);
	else
		return (0);
}

int	ft_cd(char **argv, t_environment *env)
{
	char	*cwd;
	char	*temp;
	int		error;

	cwd = ft_getenv("HOME", env);
	if (!argv[1] || !argv[1][0])
	{
		if (!cwd[0])
			return (ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO),
				1);
		error = chdir(cwd);
		return (free(cwd), error);
	}
	if (!argv[2] && argv[1][0] == '~')
	{
		temp = argv[1];
		argv[1] = str_replace(cwd, argv[1], 0, 1);
		free(temp);
	}
	free(cwd);
	if (!argv[2])
		return (ft_cd_with_arg(argv[1]));
	ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
	return (1);
}

int	ft_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (1);
	ft_putendl_fd(buff, STDOUT_FILENO);
	free(buff);
	return (0);
}
