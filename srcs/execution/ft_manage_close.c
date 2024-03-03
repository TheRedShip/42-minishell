/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:43:40 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 16:10:22 by rgramati         ###   ########.fr       */
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
	if (command->heredoc > 2)
		close(command->heredoc);
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

void	ft_close_executer(t_executer *ex)
{
	t_pipes	*tmp_pipe;
	t_pid	*tmp_pid;

	if (!ex)
		return ;
	while (ex->pipes)
	{
		tmp_pipe = ft_pipes_pop(&(ex->pipes));
		if (tmp_pipe->fd[0] > 2)
			close(tmp_pipe->fd[0]);
		if (tmp_pipe->fd[1] > 2)
			close(tmp_pipe->fd[1]);
		free(tmp_pipe);
	}
	while (ex->pids)
	{
		tmp_pid = ft_pid_pop(&(ex->pids));
		free(tmp_pid);
	}
}

void	ft_close_pipes(t_pipes *tmp_pipe)
{
	if (!tmp_pipe)
		return ;
	while (tmp_pipe)
	{
		if (tmp_pipe->fd[0] > 2)
			close(tmp_pipe->fd[0]);
		if (tmp_pipe->fd[1] > 2)
			close(tmp_pipe->fd[1]);
		tmp_pipe = tmp_pipe->next;
	}
}
