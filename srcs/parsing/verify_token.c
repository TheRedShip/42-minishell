/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:56:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/04 14:10:10 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_verify_double_token(t_token *tokens)
{
	if (tokens->type == TK_BINOPS || tokens->type == TK_PIPEXS)
		return (tokens->type);
	while (tokens->next)
	{
		if (tokens->type == TK_BINOPS && \
		(tokens->next->type == TK_BINOPS || tokens->next->type == TK_PIPEXS))
			return (tokens->type);
		else if (!ft_strncmp(tokens->str, "(", 2) && \
		(tokens->next->type == TK_BINOPS || tokens->next->type == TK_PIPEXS))
			return (tokens->type);
		else if (!ft_strncmp(tokens->str, ")", 2) && \
		(tokens->next->type == TK_REDIRS || tokens->next->type == TK_STRING))
			return (tokens->type);
		else if (tokens->type == TK_REDIRS && tokens->next->type != TK_STRING)
			return (tokens->type);
		else if (tokens->type == TK_PIPEXS && \
		(tokens->next->type == TK_PIPEXS || tokens->next->type == TK_BINOPS))
			return (tokens->type);
		tokens = tokens->next;
	}
	if (tokens->type != TK_BINOPS && tokens->type != TK_PIPEXS && tokens->type != TK_REDIRS)
		return (42);
	return (tokens->type);
}

int		ft_verify_token(t_token *tokens)
{
	if (ft_verify_double_token(tokens) != 42)
		return (0);
	return (1);
}