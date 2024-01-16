/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:15:52 by rgramati          #+#    #+#             */
/*   Updated: 2023/11/02 21:02:21 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	i = n;
	s = src;
	d = dest;
	if (dest > src)
	{
		while (i > 0)
		{
			*(d + i - 1) = *(s + i - 1);
			i--;
		}
	}
	else
		ft_memcpy(d, s, n);
	return (dest);
}
