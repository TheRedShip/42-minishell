/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/06 15:00:59 by rgramati         ###   ########.fr       */
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
		prev->next = tmp->next;
		*tokens = prev->next;
		ft_del_token(tmp);
	}
	else
	{
		tmp = *tokens;
		*tokens = tmp->next;
		ft_del_token(tmp);
	}
}

void	ft_display_token(t_token *token)
{
	printf("- TOKEN --- %p\n", token);
	printf("STRING : %s\n", token->str);
	printf("TYPE   : %u\n", token->type);
	if (token->next)
		printf("NEXT   : %p\n", token->next);
	printf("---------\n");
}

t_token	*ft_dup_token(t_token *token)
{
	t_token	*cpy;

	cpy = malloc(sizeof(t_token));
	if (!cpy)
		return (NULL);
	cpy->str = ft_strdup(token->str);
	cpy->type = token->type;
	cpy->next = NULL;
	return (cpy);
}

void	ft_del_token(t_token *token)
{
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
