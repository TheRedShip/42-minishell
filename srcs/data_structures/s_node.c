/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:28:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 11:52:02 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_init_node(int rank, void *element)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->rank = rank;
	new_node->element = element;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	ft_insert_parent(t_node **tree, t_node *root, int side)
{
	if (!tree || !root)
		return ;
	if (!(*tree))
	{
		*tree = root;
		return ;
	}
	if (side == LEFT)
		root->left = *tree;
	else
		root->right = *tree;
	*tree = root;
}

void	ft_insert_child(t_node **tree, t_node *child, int side)
{
	if (!tree || !child)
		return ;
	if (!(*tree))
	{
		*tree = child;
		return ;
	}
	if (side == LEFT)
		(*tree)->left = child;
	else
		(*tree)->right = child;
}

void	ft_associate(t_node **tree, t_node *neigh, void *element)
{
	if (!tree || !neigh)
		return ;
	if (!(*tree))
	{
		*tree = neigh;
		return ;
	}
	ft_insert_parent(tree, ft_init_node((*tree)->rank + 1, element), LEFT);
	ft_insert_child(tree, neigh, RIGHT);
}
