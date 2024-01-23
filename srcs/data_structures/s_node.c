/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:28:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/23 21:39:35 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_init_node(int rank, void *element)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->rank = rank;
	new_node->element = element;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}