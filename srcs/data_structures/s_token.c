/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:25:45 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 23:06:05 by rgramati         ###   ########.fr       */
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