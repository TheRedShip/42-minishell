/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:34 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/04 13:45:08 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token(char *str, t_quote_state qs)
{
	if (!str)
		return (0);
	if (((!ft_strncmp(str, "\"", 1) && (qs != QU_SINGLE))) || \
		(!ft_strncmp(str, "'", 1) && (qs != QU_DOUBLE)) || \
		(!ft_strncmp(str, " ", 1) && (qs == QU_ZERO)) || \
		(!ft_strncmp(str, "(", 1) && (qs == QU_ZERO)) || \
		(!ft_strncmp(str, ")", 1) && (qs == QU_ZERO)))
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
	// printf("|DEBUG| working str = [%s], qs = [%u]\n", str, qs);
	len = ft_is_token(tmp, qs);
	ft_qs_update(*tmp, &qs);
	while (*tmp && (!len || (*tmp == ' ' && qs != QU_ZERO)))
	{
		ft_qs_update(*(tmp++), &qs);
		len = ft_is_token(tmp, qs);
	}
	if (tmp == str)
		tstring = ft_strndup(str, len);
	else
		tstring = ft_strndup(str, tmp - str);
	// printf("|DEBUG| tstring = [%s], qs = [%u]\n", tstring, qs);
	if (ft_strncmp(tstring, " ", 2))
		token = ft_init_token(ft_strdup(tstring), ft_ttyper(str, qs));
	ft_add_token(&token, ft_tokenizer(str + ft_strlen(tstring), qs));
	free(tstring);
	return (token);
}

int		ft_valid_braces(t_token *tokens)
{
	int	has_binary_op;
	
	has_binary_op = 0;
	// printf("i check \n");
	// ft_display_token(tokens);
	if (!tokens)
		return (1);
	while (tokens->next && tokens->type != 1)
	{
		if (tokens->type == 2)
			has_binary_op = 1;
		tokens = tokens->next;
	}
	return (has_binary_op);
}

// int main(void)
// {
// 	t_token *t;
// 	t_token *tmp;

// 	t = ft_tokenizer("<Makefile && \" waj || \"(      echo a  echo b) | cat -e", QU_ZERO);

// 	tmp = t;
// 	while (tmp)
// 	{
// 		ft_display_token(tmp);
// 		tmp = tmp->next;
// 	}
// 	tmp = t;
// 	while (tmp)
// 	{
// 		printf(" [%s] ", tmp->str);
// 		tmp = tmp->next;
// 	}
// 	printf("\n|%d|\n", ft_valid_braces(t));
// 	printf("\n");
// 	ft_clear_token_list(t);
// 	exit(EC_SUCCES);
// }
