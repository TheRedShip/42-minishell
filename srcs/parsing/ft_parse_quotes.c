/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/05 20:08:14 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote_enforcer(char **str, t_quote_state qs)
{
	char			*string_holder;
	char			*dquote_holder;

	if (!*str)
		return ;
	string_holder = *str;
	while (**str)
		ft_qs_update(*((*str)++), &qs);
	if (qs)
	{
		dquote_holder = ft_open_dquote(qs);
		if (!dquote_holder)
		{
			free(dquote_holder);
			*str = string_holder;
			return ;
		}
		dquote_holder = ft_strjoin(string_holder, dquote_holder, "\n", 0b01);
		ft_quote_enforcer(&dquote_holder, QU_ZERO);
		*str = dquote_holder;
		return ;
	}
	*str = string_holder;
}
int	ft_quote_syntax(char *str, t_quote_state qs)
{
	while (*str)
		ft_qs_update(*(str++), &qs);
	return (!qs);
}
