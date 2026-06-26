/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:23:27 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/06 14:45:36 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static void	*ft_free_split(char **array, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
	return (NULL);
}

static int	ft_word_count(char const *s, char set)
{
	int	in_word;
	int	word_count;
	int	i;

	i = 0;
	in_word = 0;
	word_count = 0;
	if (set == '\0')
		return (word_count = (int)1);
	else
	{
		while (s[i])
		{
			if (s[i] == set)
				in_word = 0;
			else if (!(s[i] == set) && !in_word)
			{
				word_count++;
				in_word = 1;
			}
			i++;
		}
	}
	return (word_count);
}

static char	**ft_create_array(char const *s, char set)
{
	char	**array;
	int		word_count;

	word_count = ft_word_count(s, set);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (NULL);
	return (array);
}

static int	ft_next_set(char const *s, char set)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == set))
		i++;
	return (i);
}

char	**ft_split(char const *s, char set)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = ft_create_array(s, set);
	if (!array)
		return (NULL);
	while (j < ft_word_count((char *)s, set) && i < (int)ft_strlen(s))
	{
		while ((s[i] == set))
			i++;
		array[j] = ft_calloc((ft_next_set(&s[i], set)) + 1, sizeof(char));
		if (!array[j])
			return (ft_free_split(array, j));
		ft_strlcpy(array[j++], &s[i], ft_next_set(&s[i], set) + 1);
		i += ft_next_set(&s[i], set);
	}
	return (array[j] = NULL, array);
}
