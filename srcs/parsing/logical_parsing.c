/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 22:26:21 by rgramati         ###   ########.fr       */
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

int	ft_quote_checker(char *str)
{
	t_quote_state	tmp;
	t_quote_state	qs;
	int				counts[2] = {0, 0};

	qs = QU_ZERO;
	while (*str)
	{
		tmp = qs;
		if (ft_qs_update(*str, &qs))
		{
			// printf("[%c] quote state changed of %d -- to %d\n", *str, abs((int)tmp - (int)qs), qs);
			counts[abs((int)tmp - (int)qs) - 1]++;
			str++;
			continue ;
		}
		// printf("%c\n", *str);
		str++;
	}
	// printf("%d single quotes,  %d double quotes\n", counts[0], counts[1]);
	return (1);
}

// Sa""'lut" 'com"ent' tu v"'''"''"'"as"