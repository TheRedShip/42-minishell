/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:48:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/19 17:01:18 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size, int null_term)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (len > size)
		return (ft_strlen(src) + size);
	if (!*(src + i))
		return (len);
	while (*(src + i) && i + len + 1 < size)
	{
		*(dst + len + i) = *(src + i);
		i ++;
	}
	if (null_term == 1)
		*(dst + len + i) = '\0';
	while (*(src + i))
		i++;
	return (len + i);
}
