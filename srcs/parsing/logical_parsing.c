/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 13:31:37 by rgramati         ###   ########.fr       */
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

char	*ft_quote_checker(char *str, t_quote_state oldqs)
{
	t_quote_state	qs;
	char			*string_holder;
	char			*dquote_holder;

	if (!str)
		return NULL;
	qs = oldqs;
	string_holder = str;
	while (*str)
	{
		if (ft_qs_update(*str, &qs))
		{
			str++;
			continue ;
		}
		str++;
	}
	if (qs)
	{
		dquote_holder = ft_strjoin(string_holder, ft_open_dquote(qs));
		free(string_holder);
		return (ft_quote_checker(dquote_holder, QU_ZERO));
	}
	return (string_holder);
}

// int main(void)
// {
// 	char *test = "salut '\"c'a 'v'\"a\"'\"";
// 	ft_quote_checker(ft_strdup(test), QU_ZERO);
// }

// Sa""'lut" 'com"ent' tu v"'''"''"'"as"
