/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_auth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:56:54 by marvin            #+#    #+#             */
/*   Updated: 2024/03/03 18:52:01 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sub_valid_token(t_token *t)
{
	t_token_type	bops;
	t_token_type	strs;

	bops = TK_BINOPS | TK_PIPEXS;
	strs = TK_STRING | TK_REDIRS;
	if ((t->type & TK_BINOPS) && (t->next->type & bops))
		return (0);
	else if (t->type == TK_REDIRS && !(t->next->type & TK_STRING))
		return (0);
	else if (t->type == TK_PIPEXS && (t->next->type & bops))
		return (0);
	else if (!ft_strncmp(t->str, "(", 2) && ((t->next->type & bops) || \
			!ft_strncmp(t->next->str, ")", 2)))
		return (0);
	else if (t->type == TK_STRING && (t->next->type & TK_BRACES) && \
			!ft_strncmp(t->next->str, "(", 2))
		return (0);
	else if (!ft_strncmp(t->str, ")", 2) && (t->next->type & strs || \
			!ft_strncmp(t->next->str, "(", 2)))
		return (0);
	return (1);
}

int	ft_valid_token(t_token *t, char **err_token)
{
	if (t->type & (TK_BINOPS | TK_PIPEXS))
		return (0);
	while (t->next)
	{
		*err_token = t->next->str;
		if (!ft_sub_valid_token(t))
			return (0);
		t = t->next;
	}
	return (t->type & (TK_BRACES | TK_STRING));
}

int	ft_verify_brace(t_token *tokens)
{
	int	braces;

	braces = 0;
	while (tokens != NULL)
	{
		if ((tokens->type & TK_BRACES) && !ft_strncmp(tokens->str, "(", 2))
			braces++;
		else if ((tokens->type & TK_BRACES) && !ft_strncmp(tokens->str, ")", 2))
			braces--;
		if (braces < 0)
			return (0);
		tokens = tokens->next;
	}
	return (braces == 0);
}

int	ft_verify_token(t_token *tokens, char **err_token)
{
	t_token	*tmp;
	int		hdcount;

	*err_token = tokens->str;
	if (!ft_valid_token(tokens, err_token) || !ft_verify_brace(tokens))
		return (ERR_FAILED);
	tmp = tokens;
	hdcount = 0;
	while (tmp)
	{
		hdcount += ((tmp->type & TK_REDIRS) && !ft_strncmp(tmp->str, "<<", 3));
		tmp = tmp->next;
	}
	if (hdcount > 16)
		return (0b100);
	return (ERR_NOERRS);
}

int	ft_verif_binop_brace(t_token *tk)
{
	int		isvalid;
	int		level;

	level = 0;
	isvalid = 0;
	if (!tk || !(tk->type & TK_BRACES && !ft_strncmp(tk->str, "(", 2)))
		return (1);
	tk = tk->next;
	while (tk && (!(tk->type & TK_BRACES && \
		!ft_strncmp(tk->str, ")", 2)) || level))
	{
		if (tk->type & TK_BRACES && !ft_strncmp(tk->str, "(", 2))
			level++;
		if (tk->type & TK_BRACES && !ft_strncmp(tk->str, ")", 2))
			level--;
		if (!level && (tk->type & TK_BINOPS))
			isvalid = 1;
		tk = tk->next;
	}
	if (!tk)
		return (1);
	if (!(tk && isvalid))
		ft_remove_token(&tk);
	return (tk && isvalid);
}
