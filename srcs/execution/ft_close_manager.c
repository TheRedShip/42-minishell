/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:43:40 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/28 16:03:09 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_v(int nb, int fd, ...)
{
	va_list	files;
	int		i;
	int		curr;

	i = 0;
	close(fd);
	va_start(files, fd);
	while (i++ < nb)
	{
		curr = va_arg(files, int);
		if (curr >= 0)
			close(curr);
	}
	va_end(files);
}

void	ft_close_command(t_command *command)
{
	if (!command)
		return ;
	if (command->infile > 2)
		close(command->infile);
	if (command->outfile > 2)
		close(command->outfile);
}

void	ft_close_tree_rec(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		ft_close_tree_rec(tree->left);
	if (tree->right)
		ft_close_tree_rec(tree->right);
	if (tree->command)
		ft_close_command(tree->command);
}
