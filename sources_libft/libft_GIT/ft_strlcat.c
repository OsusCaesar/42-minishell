/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:22:15 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/02 14:26:29 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= siz)
		dst_len = siz;
	if (dst_len == siz)
		return (siz + src_len);
	if (src_len < siz - dst_len)
		ft_memcpy(&dst[dst_len], src, src_len + 1);
	else
	{
		ft_memcpy(&dst[dst_len], src, (siz - dst_len - 1));
		dst[siz - 1] = '\0';
	}
	return (dst_len + src_len);
}
