/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/17 15:48:25 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_quote_enforcer(char **str, int tmp_file_fd, t_quote_state qs)
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
		dquote_holder = ft_open_dquote(tmp_file_fd, qs);
		if (!dquote_holder)
		{
			free(dquote_holder);
			*str = string_holder;
			return ;
		}
		dquote_holder = ft_strjoin(string_holder, dquote_holder, "\n", 0b11);
		ft_quote_enforcer(&dquote_holder, tmp_file_fd, QU_ZERO);
		ft_static_dq_holder(dquote_holder, NULL, 0, 0b00);
		*str = dquote_holder;
		return ;
	}
	*str = string_holder;
}

char	ft_quote_syntax(char *str, t_quote_state qs)
{
	char	ret;

	ret = 0;
	while (*str)
	{
		if (ft_qs_update(*str, &qs))
			ret = *str;
		str++;
	}
	if (ret && qs)
		return (ret);
	return (0);
}

void	ft_dequote_string(char **str, t_quote_state qs)
{
	char	*tmp;
	char	*tmpr;
	char	*res;

	tmp = *str;
	res = malloc((ft_dqstrlen(*str) + 1) * sizeof(char));
	if (!res)
		return ;
	tmpr = res;
	while (*tmp)
	{
		if (ft_qs_update(*tmp, &qs))
		{
			tmp++;
			continue ;
		}
		*(tmpr++) = *(tmp++);
	}
	*tmpr = 0;
	free(*str);
	*str = res;
}
