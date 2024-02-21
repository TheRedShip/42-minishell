/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcardtest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:54:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/12 18:32:32 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_rule_wildcard(t_token **tmp, char **files)
{
	(void) tmp;
	(void) files;
	printf("|%s|\n", (*tmp)->str);
	return (files);
}

void	ft_replace_wildcard_mine(t_token **tokens, t_token **tmp)
{
	char	**files;
	char	*wcs;

	files = ft_wildcard_array((*tmp)->str);
	files = ft_rule_wildcard(tmp, files);
	free((*tmp)->str);
	wcs = ft_format_wildcard(&files);
	(*tmp)->str = ft_strdup(wcs);
	ft_wildcard_token(tokens, tmp);
	free(wcs);
}

void	ft_format_tokens_mine(t_token **tokens)
{
	t_token	*tmp;
	char	*og;

	tmp = *tokens;
	while (tmp)
	{
		og = ft_strdup(tmp->str);
		if (tmp->type & TK_STRING)
			ft_dequote_string(&(tmp->str), QU_ZERO);
		if (ft_verif_wildcard(og))
			ft_replace_wildcard_mine(tokens, &tmp);
		else
			tmp = tmp->next;
		free(og);
	}
}

int main(void)
{
	char *str = ft_strdup("salut m* cc *");

	t_token *tokens = ft_tokenizer(str, QU_ZERO);

	t_token *t;
	t = tokens;
	printf("------------- ACTUAL TOKEN LIST -------------\n");
	while (t)
	{
		printf("%p = [%s] ->", t, t->str);
		t = t->next;
	}
	printf("\n---------------------------------------------\n");

	ft_format_tokens_mine(&tokens);

	t = tokens;
	printf("------------- ACTUAL TOKEN LIST -------------\n");
	while (t)
	{
		printf("%p = [%s] ->", t, t->str);
		t = t->next;
	}
	printf("\n---------------------------------------------\n");

	free(str);
	ft_clear_token_list(tokens);
}
