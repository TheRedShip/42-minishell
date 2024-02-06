/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_auth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:56:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 16:37:35 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_valid_token(t_token *t)
{
	t_token_type	bops;
	t_token_type	strs;

	bops = TK_BINOPS | TK_PIPEXS;
	strs = TK_STRING | TK_REDIRS;
	if (t->type & bops)
		return (0);
	while (t->next)
	{
		if ((t->type & TK_BINOPS) && (t->next->type & bops))
			return (0);
		else if (!ft_strncmp(t->str, "(", 2) && (t->next->type & bops))
			return (0);
		else if (!ft_strncmp(t->str, ")", 2) && (t->next->type & strs))
			return (0);
		else if (t->type == TK_REDIRS && !(t->next->type & TK_STRING))
			return (0);
		else if (t->type == TK_PIPEXS && (t->next->type & bops))
			return (0);
		t = t->next;
	}
	if (t->type & (TK_BRACES | TK_STRING))
		return (42);
	return (0);
}

int		ft_valid_braces(t_token *tokens)
{
	int	bin;
	
	bin = 0;
	if (!tokens)
		return (1);
	while (tokens->next && !(tokens->type & TK_BRACES))
	{
		bin = (tokens->type & TK_BINOPS);
		tokens = tokens->next;
	}
	return (!bin);
}

// void	ft_delete_braces(t_token **tokens)
// {
// 	t_token	*tmp;
// 	t_token	*prev;

// 	tmp = *tokens;
// 	prev = NULL;
// 	while (tmp)
// 	{
// 		while (tmp && tmp->type != TK_BRACES)
// 		{
// 			prev = tmp;
// 			tmp = tmp->next;
// 		}
// 		if (!tmp)
// 			return ;
// 		if (ft_strncmp(tmp->str, ")", 2) && ft_valid_braces(tmp->next))
// 		{
// 			ft_remove_token(&tmp, prev);
// 			if (!prev)
// 				*tokens = tmp;
// 			while (tmp && tmp->type != TK_BRACES)
// 			{
// 				prev = tmp;
// 				tmp = tmp->next;
// 			}
// 			ft_remove_token(&tmp, prev);
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }

void	ft_remove_braces(t_token **tokens)
{
	t_token	*tmp;
	t_token	*prev;
	int		brace;

	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type & TK_BRACES)
		{
			if (ft_strncmp(tmp->str, "(", 2) && ft_valid_braces(tmp->next))
			{
				ft_remove_token(&tmp, prev);
				brace = 1;
			}
			else if (ft_strncmp(tmp->str, ")", 2) && brace)
			{
				ft_remove_token(&tmp, prev);
				brace = 0;
			}
			if (!prev)
				*tokens = tmp;
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
