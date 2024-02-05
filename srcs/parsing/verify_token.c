/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 00:56:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/04 20:40:49 by rgramati         ###   ########.fr       */
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

// int main(void)
// {
// 	char *str = ft_strdup("echo || echo && salut > toi > && cat");
// 	t_token	*tokens;
// 	t_token *tmp;

// 	tokens = ft_tokenizer(str, QU_ZERO);
// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		ft_display_token(tmp);
// 		tmp = tmp->next;
// 	}
// 	printf("ah oui la %d\n", ft_valid_token(tokens));
// 	ft_clear_token_list(tokens);
// 	free(str);
// }