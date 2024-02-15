/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:43:40 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/15 20:03:54 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_v(int nb, int fd, ...)
{
	va_list	files;
	int		i;

	i = 0;
	if (fd > 2)
		close(fd);
	va_start(files, fd);
	while (i++ < nb)
		close(va_arg(files, int));
	va_end(files);
}

void	ft_close_command(t_node *tree)
{
	if (tree->command)
	{
		if (tree->command->infile > 2)
			close(tree->command->infile);
		if (tree->command->outfile > 2)
			close(tree->command->outfile);
	}
}

void	ft_close_tree_rec(t_node *tree)
{
	if (tree->left)
		ft_close_tree_rec(tree->left);
	if (tree->right)
		ft_close_tree_rec(tree->right);
	ft_close_command(tree);
}

void	ft_close_executor(t_executor *ex)
{
	ft_close_tree_rec(ex->root);
	if (ex->input > 2)
		close(ex->input);
	if (ex->output > 2)
		close(ex->output);
	if (ex->pipes)
	{
		close(ex->pipes->fd[0]);
		close(ex->pipes->fd[1]);
	}
}
