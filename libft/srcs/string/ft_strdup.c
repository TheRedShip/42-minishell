/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:42:06 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/28 00:22:18 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*ft_strndup(char *str, size_t n)
{
	char	*cpy;
	char	*tmp;

	cpy = malloc(ft_max(n + 1, ft_strlen(str)) * sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = cpy;
	while (*str && n--)
		*(cpy++) = *(str++);
	return (tmp);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	size_t	len;

	if (!s)
		return (ft_calloc(1, 1));
	len = sizeof(char) * ft_strlen(s) + 1;
	dest = malloc(len);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, len);
	return (dest);
}
