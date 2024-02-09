/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:11:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/09 11:43:44 by rgramati         ###   ########.fr       */
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
			continue;
		}
		*(tmpr++) = *(tmp++);
	}
	*tmpr = 0;
	free(*str);
	*str = res;
}

void	ft_replace_wildcard(t_token **tokens, t_token **tmp, char **wcs)
{
	free((*tmp)->str);
	*wcs = ft_wildcard_string();
	ft_format_wildcard(wcs);
	(*tmp)->str = ft_strdup(*wcs);
	ft_wildcard_token(tokens, tmp);
	free(*wcs);
}

void	ft_format_tokens(t_token **tokens)
{
	t_token	*tmp;
	char	*wcs;
	char	*og;

	tmp = *tokens;
	while (tmp)
	{
		og = ft_strdup(tmp->str);
		if (tmp->type & TK_STRING)
			ft_dequote_string(&(tmp->str), QU_ZERO);
		if (ft_verif_wildcard(og))
			ft_replace_wildcard(tokens, &tmp, &wcs);
		else
			tmp = tmp->next;
		free(og);
	}
}

// int main(void)
// {
// 	char *str = ft_strdup("\"\"");

// 	t_token *tokens = ft_tokenizer(str, QU_ZERO);

// 	t_token *t;
// 	t = tokens;
// 	printf("------------- ACTUAL TOKEN LIST -------------\n");
// 	while (t)
// 	{
// 		printf("%p = [%s] ->", t, t->str);
// 		t = t->next;
// 	}
// 	printf("\n---------------------------------------------\n");

// 	ft_format_tokens(&tokens);

// 	t = tokens;
// 	printf("------------- ACTUAL TOKEN LIST -------------\n");
// 	while (t)
// 	{
// 		printf("%p = [%s] ->", t, t->str);
// 		t = t->next;
// 	}
// 	printf("\n---------------------------------------------\n");

// 	free(str);
// 	ft_clear_token_list(tokens);
// }
