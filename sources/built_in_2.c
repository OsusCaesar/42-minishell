/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferrand <jferrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:30:13 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 13:19:19 by jferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a partir d'ici c'est des fonctions pour ft_export
int	is_in_env(char *name, t_environment *env)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(name) + 1;
	while (env)
	{
		if (!ft_strncmp(name, env->name, size))
		{
			free(name);
			return (i);
		}
		i++;
		env = env->next;
	}
	return (-1);
}

int	add_new_env_var(char *name, char *content, t_environment *env)
{
	t_environment	*new;

	new = malloc(sizeof(t_environment));
	if (!new)
		return (ERROR_ALLOC);
	new->name = name;
	new->content = content;
	env_add_back(&env, new);
	return (0);
}

void	change_env_var(int index, char *content, t_environment *env)
{
	while (index)
	{
		env = env->next;
		index--;
	}
	free(env->content);
	env->content = content;
}

void	unvalid_name(char *message, char *name, char *content)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	free(name);
	free(content);
}

int	ft_export(char **argv, t_environment *env)
{
	char	*name;
	char	*content;
	int		in_env;

	if (!(argv[1]))
		return (env_sort(env), 0);
	while (*(++argv))
	{
		if (!ft_strchr(*argv, '='))
			return (ft_content_env_unvalid(*argv));
		name = ft_get_name_export(*argv);
		if (!name)
			return (ERROR_ALLOC);
		content = ft_get_content_env(*argv);
		if (!content)
			return (free(name), ERROR_ALLOC);
		if (!name[0])
			return (unvalid_name(ft_strchr(*argv, '='), name, content), 1);
		in_env = is_in_env(name, env);
		if (in_env == -1)
			add_new_env_var(name, content, env);
		else
			change_env_var(in_env, content, env);
	}
	return (0);
}
