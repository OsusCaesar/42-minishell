/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:34:54 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/02 12:07:57 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_bzero(void *s, size_t n)

{
	unsigned char	*buffer;
	unsigned long	i;

	i = 0;
	buffer = (unsigned char *)s;
	while (i != (unsigned long)n)
	{
		buffer[i] = 0;
		i++;
	}
}
