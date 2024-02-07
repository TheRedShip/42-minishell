/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:34 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/07 23:17:26 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token(char *str, t_quote_state qs)
{
	char		**tmp;
	static char *tokens[11] = {" ", "(", ")", "||", "&&", \
								"|", ">>", ">", "<<", "<", NULL};

	tmp = tokens;
	if (!str || !*str)
		return (0);
	while (*tmp && (ft_strncmp(str, *tmp, ft_strlen(*tmp)) || qs != QU_ZERO))
		tmp++;
	return (ft_strlen(*tmp));
}

t_token_type	ft_ttyper(char *str, t_quote_state qs)
{
	if (qs != QU_ZERO)
		return (TK_STRING);
	if (!ft_strncmp(str, "(", 1) || !ft_strncmp(str, ")", 1))
		return (TK_BRACES);
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2))
		return (TK_BINOPS);
	if (!ft_strncmp(str, "|", 1))
		return (TK_PIPEXS);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (TK_REDIRS);
	return (TK_STRING);
}

t_token	*ft_tokenizer(char *str, t_quote_state qs)
{
	t_token *token;
	char	*tstring;
	char	*tmp;
	int		len;

	token = NULL;
	if (!str || !*str)
		return (NULL);
	tmp = str;
	len = ft_is_token(tmp, qs);
	while (*tmp && (!len || (*tmp == ' ' && qs != QU_ZERO)))
	{
		ft_qs_update(*(tmp++), &qs);
		len = ft_is_token(tmp, qs);
	}
	if (tmp == str)
		tstring = ft_strndup(str, len);
	else
		tstring = ft_strndup(str, tmp - str);
	if (ft_strncmp(tstring, " ", 2))
		token = ft_init_token(ft_strdup(tstring), ft_ttyper(str, qs));
	ft_add_token(&token, ft_tokenizer(str + ft_strlen(tstring), qs));
	free(tstring);
	return (token);
}
