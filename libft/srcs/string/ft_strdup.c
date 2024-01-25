/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:42:06 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 18:26:41 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;

	if (!s)
		return ft_calloc(1, 1);
	len = sizeof(char) * ft_strlen(s) + 1;
	dest = malloc(len);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, len);
	return (dest);
}
