/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:28:17 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 16:05:13 by rgramati         ###   ########.fr       */
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
	if (!tree)
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

void	ft_associate(t_node **tree, t_node *neigh, t_command *c, t_token *t)
{
	if (!tree || !neigh)
		return ;
	if (!(*tree))
	{
		*tree = neigh;
		return ;
	}
	ft_insert_parent(tree, ft_init_node(c, t), LEFT);
	ft_insert_child(tree, neigh, RIGHT);
}

void	ft_del_node(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->token)
		ft_del_token(tree->token);
	if (tree->command)
		ft_del_command(tree->command);
	free(tree);
}

void	ft_clear_tree(t_node *tree)
{
	if (!tree)
		return ;
	ft_clear_tree(tree->left);
	ft_clear_tree(tree->right);
	if (tree->token)
		ft_del_token(tree->token);
	if (tree->command)
		ft_del_command(tree->command);
	free(tree);
}
