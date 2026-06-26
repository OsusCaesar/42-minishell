/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:04:20 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/07/19 13:34:14 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	buffer;

	sign = 1;
	buffer = 0;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' && *(nptr + 1) != '-')
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		buffer *= 10;
		buffer += (*nptr - '0');
		nptr++;
	}
	return (buffer * sign);
}
