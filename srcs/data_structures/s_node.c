/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:28:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 00:42:41 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief			Initializes a new t_node.
 * 
 * @param rank		(int)		Rank on the tree hierarchy.
 * @param element	(void *)	A pointer to struct content.
 * 
 * @return (t_node *) A pointer to the newly created t_node.
 */
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

/**
 * @brief			Insert a t_node (Parent-wise).
 * 
 * @param tree		(t_node **)	Current tree, future child.
 * @param root		(t_node *)	New root t_node.
 * @param side		(int)		Side of root where tree will be inserted.
 */
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

/**
 * @brief			Insert a t_node (Child-wise).
 * 
 * @param tree		(t_node **)	Current tree, future parent.
 * @param child		(t_node *)	New child t_node.
 * @param side		(int)		Side of tree where child will be inserted.
 */
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

/**
 * @brief			Associate 2 t_node into one tree and sets tree to \
 * @brief           newly created parent.
 * 
 * @param tree		(t_node **)	Current tree, future left child.
 * @param neigh		(t_node *)	Current 2nd tree, future right child.
 * @param element	(void *)	A pointer to the new root content
 */
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
