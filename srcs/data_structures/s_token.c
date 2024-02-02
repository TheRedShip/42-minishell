/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/02 15:14:32 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_token(t_token **tokens, t_token *next)
{
	t_token	*tmp;

	if (!tokens || !next)
		return ;
	if (!(*tokens))
	{
		*tokens = next;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
}

void	ft_remove_token(t_token **tokens, t_token *prev)
{
	t_token *tmp;

	if (prev)
	{
		tmp = *tokens;
		prev->next = (*tokens)->next;
		ft_del_token(tmp);
	}
	else
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		ft_del_token(tmp);
	}
}

void	ft_display_token(t_token *token)
{
	printf("- TOKEN --- %x ------------------\n", *(unsigned int *) token);
	printf("STRING : %s\n", token->str);
	printf("TYPE   : %u\n", token->type);
	if (token->next)
		printf("NEXT   : %x\n", *(unsigned int *) token->next);
	printf("--------------------------------------\n\n");
}

void	ft_delete_braces(t_token **tokens)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		while (tmp && tmp->type != TK_BRACES)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (!ft_valid_braces(tmp))
		{
			ft_remove_token(&tmp, prev);
			while (tmp && tmp->type != TK_BRACES)
			{
				prev = tmp;
				tmp = tmp->next;
			}
			ft_remove_token(&tmp, prev);
		}
	}
}

void	ft_del_token(t_token *token)
{
	printf("deleting token at adress %x\n", *(unsigned int *) token);
	if (!token)
		return ;
	free(token->str);
	free(token);
}

void	ft_clear_token_list(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next;
		ft_del_token(tokens);
		tokens = tmp;
	}
}

int main(void)
{
	t_token *tmp = NULL;
	char *str = ft_strdup("<Makefile cat | wc -l > /dev/stdout");

	t_token *tokens = ft_tokenizer(str, QU_ZERO);
	tmp = tokens;
	while (tmp)
	{
		ft_display_token(tmp);
		tmp = tmp->next;
	}
	ft_delete_braces(&tokens);
	printf("\n\n");
	tmp = tokens;
	while (tmp)
	{
		ft_display_token(tmp);
		tmp = tmp->next;
	}
	ft_clear_token_list(tokens);
	free(str);
}
