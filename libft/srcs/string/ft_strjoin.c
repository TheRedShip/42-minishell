/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:35:56 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 13:58:31 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_manage_strings(char *s1, char *s2, int buffered)
{
	if (buffered & 1)
		free(s1);
	if (buffered & 2)
		free(s2);
}

char	*ft_strjoin(char *s1, char *s2, char *c)
{
	char	*ns;
	int		buffered;
	size_t	len1;
	size_t	len2;

	buffered = !s1 + (2 * !s2);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ns = ft_calloc((len1 + len2 + 1 + !!c), sizeof(char));
	if (ns == NULL)
		return (ns);
	ft_strlcat(ns, s1, len1 + 1, 1);
	if (c)
		ft_strlcat(ns, c, len1 + 2, 1);
	ft_strlcat(ns, s2, len1 + len2 + 1 + !!c, 1);
	ft_manage_strings(s1, s2, buffered);
	return (ns);
}
