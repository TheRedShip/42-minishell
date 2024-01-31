/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/31 21:53:44 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_token(t_token **token, t_token *next)
{
	t_token	*tmp;

	if (!token || !next)
		return ;
	if (!(*token))
	{
		*token = next;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
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

void	*ft_convert_token(t_token *token)
{
	(void) token;
	return (NULL);
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

