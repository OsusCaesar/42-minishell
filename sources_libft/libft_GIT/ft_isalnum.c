/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecuyer <tlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:03:12 by tlecuyer          #+#    #+#             */
/*   Updated: 2025/05/02 12:20:57 by tlecuyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int argument)
{
	if ((argument > 96 && argument < 123) || (argument > 64 && argument < 91)
		|| (argument > 47 && argument < 58))
		return (1);
	else
		return (0);
}
