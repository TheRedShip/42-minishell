/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:56:34 by rgramati          #+#    #+#             */
/*   Updated: 2023/11/01 14:45:38 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	i = 0;
	str = s;
	if (!n)
		return (NULL);
	while (i < n && *(str + i) != (unsigned char)c)
		i++;
	if (i >= n && (unsigned char)c != '\0')
		return (NULL);
	return ((unsigned char *)str + i);
}
