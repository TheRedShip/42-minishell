/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 23:36:46 by rgramati         ###   ########.fr       */
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

char	*ft_open_dquote(t_quote_state qs)
{
	char	*line;

	if (qs == QU_SINGLE)
		line = readline(P_SDQUOTE);
	if (qs == QU_DOUBLE)
		line = readline(P_DDQUOTE);
	return (ft_strdup(line));
}

int	ft_quote_checker(char *str, t_quote_state oldqs)
{
	t_quote_state	qs;
	char			*string_holder;
	char			*dquote_holder;

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
		dquote_holder = ft_strjoin(str, ft_open_dquote(qs));
		free(string_holder);
		return (ft_quote_checker(dquote_holder, qs));
	}
	// printf("%d single quotes,  %d double quotes\n", counts[0], counts[1]);
	return (1);
}

int main(void)
{
	char *test = "salut '\"c'a 'v'\"a\"'\"";
	ft_quote_checker(ft_strdup(test), QU_ZERO);
}

// Sa""'lut" 'com"ent' tu v"'''"''"'"as"