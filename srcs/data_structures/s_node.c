/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:28:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 17:08:02 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_del_node(t_node *tree)
{
	if (!tree)
		return ;
	ft_del_node(tree->left);
	ft_del_node(tree->right);
	free(tree);
}
