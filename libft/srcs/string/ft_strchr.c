/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:56:29 by rgramati          #+#    #+#             */
/*   Updated: 2023/10/31 17:30:45 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	const char	*str;

	i = 0;
	str = s;
	while (*(str + i) && *(str + i) != (unsigned char)c)
		i++;
	if (!*(str + i) && (unsigned char)c != 0)
		return (NULL);
	return ((char *)str + i);
}
