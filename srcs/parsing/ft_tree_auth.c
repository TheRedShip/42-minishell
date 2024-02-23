/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_auth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:42:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/23 10:57:57 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_commands(t_node *tree)
{
	int	state;

	state = 0;
	if (!tree)
		return (state);
	if (!tree->command && !tree->token)
		return (1);
	state &= ft_check_commands(tree->left);
	state &= ft_check_commands(tree->right);
	return (state);
}
