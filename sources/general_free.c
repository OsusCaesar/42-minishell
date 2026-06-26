/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:38:44 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/10/12 22:44:59 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_free_token(t_token **head)
{
	t_token	*cpy;
	t_token	*buff;

	cpy = (*head);
	if (head && *head)
	{
		while (cpy)
		{
			buff = cpy->next;
			ft_free_part(&cpy->part_str);
			ft_free_str(&cpy->str_final);
			free(cpy);
			cpy = buff;
		}
		*head = NULL;
	}
	return (NULL);
}

t_part	*ft_free_part(t_part **head)
{
	t_part	*cpy;
	t_part	*buff;

	cpy = (*head);
	if (head && *head)
	{
		while (cpy)
		{
			buff = cpy->next;
			ft_free_str(&cpy->str);
			free(cpy);
			cpy = buff;
		}
		*head = NULL;
	}
	return (NULL);
}

char	*ft_free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (*str);
}

void	free_strtab(char **strs)
{
	int	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
			ft_free_str(&strs[i++]);
		free(strs);
	}
}

void	if_free(void *allocd)
{
	if (allocd)
		free(allocd);
}
