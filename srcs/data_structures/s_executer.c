/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_executer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:26:39 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/28 19:41:17 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_executer	*ft_init_executer(void)
{
	t_executer	*new_ex;

	new_ex = malloc(sizeof(t_executer));
	if (!new_ex)
		return (NULL);
	new_ex->pids = NULL;
	new_ex->pipes = NULL;
	return (new_ex);
}

