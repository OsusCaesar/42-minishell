/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:44:41 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/02 12:12:02 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*buffer;
	size_t			i;

	i = 0;
	buffer = ((unsigned char *)malloc(nmemb * size));
	if (!buffer)
		return (NULL);
	while (i < nmemb * size)
	{
		buffer[i] = 0;
		i++;
	}
	return (buffer);
}
