/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:56:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/29 18:11:10 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = s;
	while (*(str + i) && *(str + i) != (unsigned char)c)
		i++;
	if (!*(str + i) && (unsigned char)c != 0)
		return (NULL);
	return ((char *)str + i);
}
