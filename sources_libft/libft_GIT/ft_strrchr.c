/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:03:18 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/05 12:37:35 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*adress;

	i = 0;
	adress = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			adress = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		adress = (char *)&s[i];
	return (adress);
}
