/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 23:22:23 by marvin           ###   ########.fr       */
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
		dquote_holder = ft_strjoin(string_holder, ft_open_dquote(qs), "\n", 2);
		free(string_holder);
		return (ft_quote_checker(dquote_holder, QU_ZERO));
	}
	return (string_holder);
}
