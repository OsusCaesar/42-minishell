/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:44:51 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/02 13:31:06 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*buffer;
	unsigned char	*buffer_src;

	i = 0;
	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	buffer = (unsigned char *)dest;
	buffer_src = (unsigned char *)src;
	while (i < n)
	{
		buffer[i] = buffer_src[i];
		i++;
	}
	return (buffer);
}
