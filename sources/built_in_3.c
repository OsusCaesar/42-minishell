/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:30:13 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:31:28 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, t_environment *env)
{
	t_environment	*iter;
	t_environment	*tmp;

	while (*(++argv))
	{
		iter = env;
		while (iter)
		{
			if (!ft_strncmp(iter->name, *argv, ft_strlen(*argv) + 1))
			{
				if (iter->prev)
					iter->prev->next = iter->next;
				if (iter->next)
					iter->next->prev = iter->prev;
				free(iter->name);
				free(iter->content);
				tmp = iter;
				iter = iter->next;
				free(tmp);
			}
			else
				iter = iter->next;
		}
	}
	return (0);
}

int	ft_env(char **argv, t_environment *env)
{
	if (argv[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (1);
	}
	while (env)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	return (0);
}

int	ft_exit(char **argv, t_environment **env)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_free_env(env);
	rl_clear_history();
	if (!argv || !argv[1])
		exit(g_exit_status);
	if (!is_atoi_valid(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		exit(1);
	}
	if (is_atoi_valid(argv[1]))
		exit(ft_atoi(argv[1]));
	return (0);
}

int	is_atoi_valid(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if ((str[i] == '-' || str[i] == '+'))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
