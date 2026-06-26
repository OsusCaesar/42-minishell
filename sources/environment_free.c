/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:42:07 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/10 18:27:14 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_environment **head)
{
	t_environment	*cpy;
	t_environment	*buf;

	if (!head || !*head)
		return ;
	cpy = *head;
	while (cpy)
	{
		buf = cpy->next;
		ft_free_str(&cpy->name);
		ft_free_str(&cpy->content);
		free(cpy);
		cpy = buf;
	}
	*head = NULL;
}

// t_environment	*env_sort(t_environment *head)
// {
// 	char			*buff;
// 	t_environment	*cpy_x;
// 	t_environment	*cpy_y;

// 	cpy_x = head;
// 	while (cpy_x)
// 	{
// 		cpy_y = cpy_x;
// 		while (cpy_y)
// 		{
// 			if (ft_strncmp(cpy_y->name, cpy_x->name,
// 					ft_strlen(cpy_y->name)) < 0)
// 			{
// 				buff = cpy_y->name;
// 				cpy_y->name = cpy_x->name;
// 				cpy_x->name = buff;
// 				buff = cpy_y->content;
// 				cpy_y->content = cpy_x->content;
// 				cpy_x->content = buff;
// 			}
// 			cpy_y = cpy_y->next;
// 		}
// 		cpy_x = cpy_x->next;
// 	}
// 	return (head);
// }

t_environment	*env_sort(t_environment *head)
{
	char	**env_char;
	char	*buffer;
	int		i;
	int		j;

	j = 0;
	i = 0;
	env_char = env_to_char(head);
	while (env_char[i])
	{
		j = i;
		while (env_char[j])
		{
			if (ft_strncmp(env_char[j], env_char[i],
					ft_strlen(env_char[j])) < 0)
			{
				buffer = env_char[j];
				env_char[j] = env_char[i];
				env_char[i] = buffer;
			}
			j++;
		}
		i++;
	}
	return (ft_print_db_char(env_char), head);
}

void	ft_print_db_char(char **env_char)
{
	int	i;

	i = 0;
	while (env_char[i])
	{
		printf("export %s\n", env_char[i]);
		i++;
	}
	free_strtab(env_char);
}
