/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/26 14:13:06 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_qs_update(char c, t_quote_state *qs)
{
	t_quote_state	tmp;

	tmp = *qs;
	if (*qs == QU_ZERO)
	{
		if (c == '\'')
			*qs = QU_SINGLE;
		if (c == '"')
			*qs = QU_DOUBLE;
	}
	else if ((c == '\'' && *qs == QU_SINGLE) || (c == '"' && *qs == QU_DOUBLE))
		*qs = QU_ZERO;
	return (*qs != tmp);
}

char	*str_add(char *dest, char *src, size_t place)
{
	size_t	i;
	int		j;
	size_t	k;
	char *final_str;

	final_str = malloc(sizeof(char) * ft_strlen(dest) + ft_strlen(src) + 1);
	if (!final_str)
		return (NULL);
	final_str[ft_strlen(dest) + ft_strlen(src)] = '\0';
	i = -1;
	k = 0;
	while (++i < ft_strlen(dest) + ft_strlen(src))
	{
		if (i == place)
		{
			j = -1;
			while (src[++j])
				final_str[k++] = src[j];  
		}
		if (k < ft_strlen(dest) + ft_strlen(src))
			final_str[k] = dest[i];
		k++;
	}
	free(dest);
	return (final_str);
}

char	*str_append(char *str, char c)
{
	int		i;
    int 	len;
    char 	*new_str;

    len = ft_strlen(str);
    new_str = (char *)malloc(len + 2);
    if (!new_str)
        return (NULL);
    i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
    new_str[len] = c;
    new_str[len + 1] = '\0';
	if (str != NULL)
    	free(str);
    return (new_str);
}