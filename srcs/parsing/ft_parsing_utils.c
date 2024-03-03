/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:40 by ycontre           #+#    #+#             */
/*   Updated: 2024/03/03 18:53:23 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_qs_update(char c, t_qstate *qs)
{
	t_qstate	tmp;

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

int	ft_dqstrlen(char *str)
{
	t_qstate	qs;
	int			len;

	qs = QU_ZERO;
	len = 0;
	while (*str)
	{
		if (!ft_qs_update(*(str++), &qs))
			len++;
	}
	return (len);
}

void	ft_remove_braces(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (!ft_verif_binop_brace(tmp))
		{
			ft_remove_token(&tmp);
			if (!tmp)
			{
				*tokens = NULL;
				continue ;
			}
			if (!tmp->prev)
				*tokens = tmp;
			continue ;
		}
		tmp = tmp->next;
	}
}
