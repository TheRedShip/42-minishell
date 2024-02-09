/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/09 15:42:02 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_node *cmd_tree)
{
	t_node	*tmp;

	tmp = cmd_tree;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->token && (tmp->token->type & TK_PIPEXS))
			ft_pipe_exec(tmp);
	}
}

void	ft_pipe_exec(t_node *cmd_tree)
{
	
}
