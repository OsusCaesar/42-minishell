/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:45:03 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/06 14:38:15 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*buffer;

	while (lst)
	{
		buffer = lst->next;
		f(lst->content);
		lst = buffer;
	}
}
