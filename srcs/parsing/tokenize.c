/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:34 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/01 15:53:20 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token(char *str, t_quote_state qs)
{
	if (!ft_strncmp(str, "\"", 1))
		return (1);
	else if (!ft_strncmp(str, "'", 1))
		return (1);
	else if (!ft_strncmp(str, " ", 1) && (qs == QU_ZERO))
		return (1);
	else if (!ft_strncmp(str, "(", 1) && (qs == QU_ZERO))
		return (1);
	else if (!ft_strncmp(str, ")", 1) && (qs == QU_ZERO))
		return (1);
	else if (!ft_strncmp(str, "||", 2) && (qs == QU_ZERO))
		return (2);
	else if (!ft_strncmp(str, "&&", 2) && (qs == QU_ZERO))
		return (2);
	else if (!ft_strncmp(str, "|", 1) && (qs == QU_ZERO))
		return (1);
	else if (!ft_strncmp(str, ">>", 2) && (qs == QU_ZERO))
		return (2);
	else if (!ft_strncmp(str, ">", 1) && (qs == QU_ZERO))
		return (1);
	else if (!ft_strncmp(str, "<<", 2) && (qs == QU_ZERO))
		return (2);
	else if (!ft_strncmp(str, "<", 1) && (qs == QU_ZERO))
		return (1);
	return (0);
}

// int	ft_is_token(char *str, t_quote_state qs)
// {
// 	return (\
// 	(!ft_strncmp(str, "||", 2) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, "&&", 2) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, ">>", 2) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, "<<", 2) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, "\"", 1) && (qs == QU_DOUBLE)) || \
// 	(!ft_strncmp(str, "'", 1) && (qs == QU_SINGLE)) || \
// 	(!ft_strncmp(str, " ", 1) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, "(", 1) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, ")", 1) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, "|", 1) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, ">", 1) && (qs == QU_ZERO)) || \
// 	(!ft_strncmp(str, "<", 1) && (qs == QU_ZERO)));
// }

t_token_type	ft_ttyper(char *str)
{
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
	if (!*str)
		return (NULL);
	tmp = str;
	printf("|DEBUG| working str = [%s], qs = [%u]\n", str, qs);
	len = ft_is_token(tmp, qs);
	ft_qs_update(*tmp, &qs);
	while (!len || (*tmp == ' ' && qs != QU_ZERO))
	{
		ft_qs_update(*tmp, &qs);
		tmp++;
		len = ft_is_token(tmp, qs);
	}
	if (tmp == str)
		tstring = ft_strndup(str, len);
	else
		tstring = ft_strndup(str, tmp - str);
	printf("|DEBUG| tstring = [%s], qs = [%u]\n", tstring, qs);
	if (ft_strncmp(tstring, " ", 2))
		token = ft_init_token(ft_strdup(tstring), ft_ttyper(str));
	ft_add_token(&token, ft_tokenizer(str + ft_strlen(tstring), qs));
	free(tstring);
	return (token);
}

// int main(void)
// {
// 	t_token *t;
// 	t_token *tmp;

// 	t = ft_tokenizer("Makefile cat -e && echo            $HOME || salut | ouiii       > out", QU_ZERO);

// 	tmp = t;
// 	while (tmp)
// 	{
// 		ft_display_token(tmp);
// 		tmp = tmp->next;
// 	}
// 	tmp = t;
// 	while (tmp)
// 	{
// 		printf("[%s]", tmp->str);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// 	ft_clear_token_list(t);
// 	exit(EC_SUCCES);
// }
