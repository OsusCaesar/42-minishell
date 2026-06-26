/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:14:32 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/07/27 17:06:30 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;

	i = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(sizeof(char) * i + 1);
	if (!new_string)
		return (NULL);
	ft_memcpy(new_string, s1, ft_strlen(s1)+1);
	ft_memcpy(new_string + ft_strlen(s1), s2, ft_strlen(s2)+1);
	return (new_string);
}
