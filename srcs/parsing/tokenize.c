/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:34 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/31 21:56:27 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token(char *str, t_quote_state qs)
{
	if (!ft_strncmp(str, "\"", 1) && (qs == QU_DOUBLE))
		return (1);
	else if (!ft_strncmp(str, "'", 1) && (qs == QU_SINGLE))
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

// int	ft_is_token(char *str, t_quote_state qs, t_token_type *tt)
// {
// 	*tt = TK_STRING;
// 	if (qs == QU_ZERO)
// 	{
// 		if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2))
// 			*tt = TK_BINOPS;
// 	}
// }

t_token	*ft_tokenizer(char *str, t_quote_state qs)
{
	t_token			*token;
	// t_token_type	tt;
	char			*last;
	char			*test;
	char			*tmp;
	long int		len;
	
	token = NULL;
	last = str;
	while (*str)
	{
		ft_qs_update(*str, &qs);
		len = ft_is_token(str, qs);
		if (len)
		{
			test = ft_strndup(last, str - last);
			tmp = ft_strtrim(test, " ");
			last = ft_strtrim(tmp, "\"'");
			free(tmp);
			if (*last)
				ft_add_token(&token, ft_init_token(ft_strdup(last), 0));
			free(last);
			last = str;
		}
		if (!len)
			str++;
		else
			str += len;
	}
	test = ft_strndup(last, str - last);
	tmp = ft_strtrim(test, " ");
	last = ft_strtrim(tmp, "\"'");
	free(tmp);
	ft_add_token(&token, ft_init_token(ft_strdup(last), 0));
	free(last);
	
	return (token);
}

// int main(void)
// {
// 	t_token *t;
// 	t_token *tmp;

// 	t = ft_tokenizer("< Makefile cat -e && echo $HOME || salut | ouiii       > out", QU_ZERO);

// 	tmp = t;
// 	while (tmp)
// 	{
// 		ft_display_token(tmp);
// 		tmp = tmp->next;
// 	}
// 	ft_clear_token_list(t);
// 	exit(EC_SUCCES);
// }
