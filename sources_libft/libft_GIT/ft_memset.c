/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:01:22 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/04/27 17:29:16 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*buffer;
	unsigned long	i;

	i = 0;
	buffer = (unsigned char *)s;
	while (i != (unsigned long)n)
	{
		buffer[i] = (unsigned char)c;
		i++;
	}
	return (buffer);
}
