/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:39:34 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:39:09 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_char(t_environment *env)
{
	t_environment	*cpy;
	char			**envp;
	int				i;

	i = 0;
	cpy = env;
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	cpy = env;
	i = 0;
	while (cpy)
	{
		envp[i] = ft_get_str_env(cpy);
		cpy = cpy->next;
		i++;
	}
	envp[i] = NULL;
	i = 0;
	return (envp);
}

char	*ft_get_str_env(t_environment *cpy)
{
	char	*str;
	char	*buffer;

	buffer = ft_strjoin(cpy->name, "=");
	if (!buffer)
		return (NULL);
	str = ft_strjoin(buffer, cpy->content);
	if (!str)
		return (NULL);
	free(buffer);
	return (str);
}
