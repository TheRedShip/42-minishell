/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:32:18 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/14 01:41:01 by rgramati         ###   ########.fr       */
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
	return (new_ex);
}
