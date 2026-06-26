/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:15:40 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/11 23:09:29 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, int size)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(size + 1);
	if (!dup)
		return (NULL);
	while (s[i] && i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// Rajoute le char c a la fin du string str
// avec une reallocation mémoire
char	*str_cat_plus(char **str, char c)
{
	char	*new_str;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen((*str)) + 2;
	new_str = malloc(sizeof(char) * length);
	if (!new_str)
		return (NULL);
	while (i < length - 2)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	new_str[++i] = '\0';
	free(*str);
	*str = NULL;
	*str = new_str;
	return (*str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_string;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(sizeof(char) * i + 1);
	if (!new_string)
		return (NULL);
	ft_memcpy(new_string, s1, ft_strlen(s1) + 1);
	ft_memcpy(new_string + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (new_string);
}

// Ajoute str_final à la fin de argv en réallouant la mémoire
char	**cat_argv(char **argv, char *str_final)
{
	int		i;
	int		j;
	char	**new_argv;

	i = 0;
	j = 0;
	if (!str_final)
		return (NULL);
	while (argv && argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return (free(argv), NULL);
	while (j < i)
	{
		new_argv[j] = argv[j];
		j++;
	}
	new_argv[j++] = ft_strdup(str_final);
	new_argv[j] = NULL;
	if (argv)
		free(argv);
	return (new_argv);
}

int	ft_cmd_size(t_cmd *cmd)
{
	int	size;

	{
		size = 0;
		while (cmd)
		{
			size++;
			cmd = cmd->next;
		}
		return (size);
	}
}
