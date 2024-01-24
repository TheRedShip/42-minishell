/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 13:56:08 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_init_token(char *str, t_token_type type)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = str;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	ft_add_token(t_token **token, t_token *next)
{
	if (!token || !next)
		return ;
	if (!(*token))
	{
		*token = next;
		return ;
	}
	(*token)->next = next;
}

void	*ft_convert_token(t_token *token)
{
	(void) token;
	return (NULL);
}

void	ft_del_token(t_token *token)
{
	if (!token)
		return ;
	free(token->str);
	free(token);
}