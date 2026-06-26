/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:42:15 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/06 14:18:49 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_new_content(t_list *lst, t_list *start, void (*del)(void *),
		void *(*f)(void *))
{
	void	*new_content;
	t_list	*new_lst;

	new_content = f(lst->content);
	new_lst = ft_lstnew(new_content);
	if (!new_lst)
	{
		del(new_content);
		ft_lstclear(&start, del);
		return (NULL);
	}
	return (new_lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*start;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		new_lst = ft_new_content(lst, start, del, f);
		if (!new_lst)
			return (NULL);
		if (!start)
		{
			start = new_lst;
			current = new_lst;
		}
		else
		{
			current->next = new_lst;
			current = new_lst;
		}
		lst = lst->next;
	}
	return (start);
}
