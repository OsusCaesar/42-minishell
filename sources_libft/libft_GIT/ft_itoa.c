/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:47:15 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/06 14:18:01 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static long	ft_sizealloc(long n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	size;
	long	nb;
	char	*num;

	nb = n;
	size = ft_sizealloc(nb);
	num = malloc((size + 1) * sizeof(char));
	if (!num)
		return (NULL);
	*(num + size) = 0;
	*num = '0';
	if (n < 0)
	{
		nb = -nb;
		*num = '-';
	}
	while (nb && size--)
	{
		*(num + size) = nb % 10 + 48;
		nb /= 10;
	}
	return (num);
}
