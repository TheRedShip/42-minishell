/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:32:18 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/25 19:05:58 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_executor	*ft_init_executor(t_node *root)
{
	t_executor	*new_ex;

	new_ex = malloc(sizeof(t_executor));
	if (!new_ex)
		return (NULL);
	new_ex->input = -1;
	new_ex->output = -1;
	new_ex->pipes = NULL;
	new_ex->root = root;
	new_ex->base = -1;
	return (new_ex);
}

void	ft_del_executor(t_executor *ex)
{
	if (ex->pipes)
		ft_del_pipe(ex->pipes);
	free(ex);
}
