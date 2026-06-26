/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:13:18 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/01 20:11:24 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;
	unsigned int	size;

	if (!s || !f)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	new_str = ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = (*f)(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
