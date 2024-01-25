/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 17:08:18 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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