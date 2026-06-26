/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:44:11 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/05 19:15:44 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, int n)
{
	unsigned char	*memory_src;
	unsigned char	*memory_dest;
	int				i;

	if (!dest && !src)
		return (0);
	memory_dest = (unsigned char *)dest;
	memory_src = (unsigned char *)src;
	i = 0;
	if (memory_dest > memory_src && memory_src + n > memory_dest)
		while (n--)
			memory_dest[n] = memory_src[n];
	else
	{
		while (i < n)
		{
			memory_dest[i] = memory_src[i];
			i++;
		}
	}
	return (dest);
}
