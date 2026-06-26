/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:39:34 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/13 14:32:32 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environment	*ft_cpy_env(char **env)
{
	t_environment	*new;
	t_environment	*head;
	int				i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	head = NULL;
	while (env[i])
	{
		new = malloc(sizeof(t_environment));
		if (!new)
		{
			free(head);
			return (NULL);
		}
		new->name = ft_get_name(env[i]);
		new->content = ft_get_content_env(env[i]);
		env_add_back(&head, new);
		i++;
	}
	return (head);
}

char	*ft_get_name(char *line)
{
	int		i;
	char	*name;

	i = 0;
	while (line[i] != '=')
		i++;
	name = strndup(line, i);
	if (!name)
		return (NULL);
	return (name);
}

// renvoyer chaine vide si le nom est pas valide
char	*ft_get_name_export(char *line)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	if (line[0] != '_' && !ft_isalpha(line[0]))
		return (ft_strdup(""));
	while (line[i] && line[i] != '=' && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	while (line[j] && line[j] != '=')
		j++;
	if (i != j)
		return (ft_strdup(""));
	name = strndup(line, i);
	if (!name)
		return (NULL);
	return (name);
}

char	*ft_get_content_env(char *line)
{
	int		i;
	char	*content;

	i = 0;
	while (line[i] != '=')
		i++;
	content = strndup(&line[i + 1], ft_strlen(&line[i]));
	if (!content)
		return (NULL);
	return (content);
}

int	ft_content_env_unvalid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((i == 0 && !ft_isalpha(line[i]) && line[i] != '_')
			|| (i != 0 && !ft_isalnum(line[i]) && line[i] != '_'))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(line, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
