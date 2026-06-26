/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:58:09 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/06 14:19:53 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_creat_string(char *s1, int start, int len);

static int	ft_is_set(char c, char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static char	*ft_creat_string(char *s1, int start, int len)
{
	char	*final_string;

	if (len <= 0 || start >= (int)ft_strlen(s1))
		return (ft_strdup(""));
	final_string = ft_calloc(len + 1, sizeof(char));
	if (!final_string)
		return (NULL);
	ft_strlcat(final_string, &s1[start], len + 1);
	return (final_string);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	j = ft_strlen(s1);
	j--;
	while (ft_is_set(s1[i], (char *)set))
		i++;
	while (ft_is_set(s1[j], (char *)set))
		j--;
	if (i > j)
		return (ft_strdup(""));
	return (ft_creat_string((char *)s1, i, (j - i) + 1));
}
