/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:35:56 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 17:52:42 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, char *c)
{
	char	*ns;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ns = ft_calloc((len1 + len2 + 1 + !!c), sizeof(char));
	if (ns == NULL)
		return (ns);
	ft_strlcat(ns, s1, len1 + 1, 1);
	if (c)
		ft_strlcat(ns, c, len1 + 2, 1);
	ft_strlcat(ns, s2, len1 + len2 + 1 + !!c, 1);
	return (ns);
}
