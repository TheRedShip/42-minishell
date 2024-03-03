/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_binops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:48:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 16:05:38 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_wait_and_or(t_executer *ex)
{
	t_pid	*towait;
	int		err_code;

	towait = ft_pid_pop(&(ex->pids));
	if (towait)
	{
		ft_close_pipes(ex->pipes);
		waitpid(towait->pid, &err_code, 0);
		ft_command_exit(err_code);
		err_code = WEXITSTATUS(err_code);
	}
	else
		err_code = g_exit_code;
	free(towait);
	return (err_code);
}

void	ft_exec_and(t_node *tree, int *node_fd, t_executer *ex)
{
	int	err_code;

	if (node_fd[0] != STDIN_FILENO)
		dup2(node_fd[0], STDIN_FILENO);
	ft_exec_mux(tree->left, node_fd, ex, EX_WAIT);
	err_code = ft_wait_and_or(ex);
	if (err_code == ERR_NOERRS)
	{
		ft_exec_mux(tree->right, node_fd, ex, EX_WAIT);
		ft_wait_and_or(ex);
	}
}

void	ft_exec_or(t_node *tree, int *node_fd, t_executer *ex)
{
	int	err_code;

	if (node_fd[0] != STDIN_FILENO)
		dup2(node_fd[0], STDIN_FILENO);
	ft_exec_mux(tree->left, node_fd, ex, EX_WAIT);
	err_code = ft_wait_and_or(ex);
	if (err_code != ERR_NOERRS)
	{
		ft_exec_mux(tree->right, node_fd, ex, EX_WAIT);
		ft_wait_and_or(ex);
	}
}
