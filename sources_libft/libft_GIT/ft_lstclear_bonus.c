/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:42:13 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/06 14:18:14 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buf;

	buf = *lst;
	while (*lst)
	{
		buf = ((*lst)->next);
		del((*lst)->content);
		free(*lst);
		*lst = buf;
	}
}
