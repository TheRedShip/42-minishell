/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 17:02:57 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		dquote_holder = ft_strjoin(string_holder, ft_open_dquote(qs), "\n");
		free(string_holder);
		return (ft_quote_checker(dquote_holder, QU_ZERO));
	}
	return (string_holder);
}

int	ft_quoted_words_counter(char *str)
{
	t_quote_state	qs;
	int				changed;
	int				count;

	changed = 0;
	count = 0;
	if (!str)
		return 0;
	while (*str)
	{
		changed = ft_qs_update(*str, &qs);
		str++;
	}
	return(0);
}
