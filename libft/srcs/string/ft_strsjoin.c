/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:26:32 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 12:31:56 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsjoin(char **strs, char *sep)
{
	int		i;
	int		size;
	char	**cpy;
	char	*join;

	size = 0;
	cpy = strs;
	while (*cpy)
		size += ft_strlen(*(cpy++));
	size += ft_tab_len(strs) * ft_strlen(sep);
	join = ft_calloc(size + 1, sizeof(char));
	i = 1;
	if (*strs)
		ft_strlcat(join, strs[0], ft_strlen(strs[0]), 1);
	while (strs[i])
	{
		ft_strlcat(join, sep, ft_strlen(sep), 1);
		ft_strlcat(join, strs[i], ft_strlen(strs[i]), 1);
		i++;
	}
	return (join);
}
