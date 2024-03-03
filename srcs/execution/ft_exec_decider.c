/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_decider.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:48:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 14:26:52 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_exec_and(t_node *tree, int *node_fd, t_executer *ex)
{
	t_pid	*towait;
	int		err_code;

	if (node_fd[0] != STDIN_FILENO)
		dup2(node_fd[0], STDIN_FILENO);

	ft_printf("[EXEC] : AND branching left to <%p> \n[%d]->[%d]\n", tree->left, node_fd[0], node_fd[1]);
	ft_exec_mux(tree->left, node_fd, ex, EX_WAIT);

	towait = ft_pid_pop(&(ex->pids));
	if (towait)
	{
		ft_close_pipes(ex->pipes);
		waitpid(towait->pid, &err_code, 0);
		ft_signal_state(SIGHANDLER_INT);
		ft_printf("[EXEC] : AND waiting for pid [%d] at <%p>\n", towait->pid, towait);
		err_code = WEXITSTATUS(err_code);
	}
	else
		err_code = g_exit_code;
	free(towait);
	if (err_code == ERR_NOERRS)
	{
		ft_printf("[EXEC] : AND branching right to <%p> \n[%d]->[%d]\n", tree->right, node_fd[0], node_fd[1]);
		ft_exec_mux(tree->right, node_fd, ex, EX_WAIT);
		towait = ft_pid_pop(&(ex->pids));
		if (towait)
		{
			ft_close_pipes(ex->pipes);
			waitpid(towait->pid, &err_code, 0);
			ft_signal_state(SIGHANDLER_INT);
			ft_printf("[EXEC] : AND waiting for pid [%d] at <%p>\n", towait->pid, towait);
			err_code = WEXITSTATUS(err_code);
		}
		else
			err_code = g_exit_code;
		free(towait);
	}
}

void	ft_exec_or(t_node *tree, int *node_fd, t_executer *ex)
{
	t_pid	*towait;
	int		err_code;

	if (node_fd[0] != STDIN_FILENO)
		dup2(node_fd[0], STDIN_FILENO);
	// ft_printf("[EXEC] : OR branching left to <%p> \n[%d]->[%d]\n", tree->left, node_fd[0], node_fd[1]);
	ft_exec_mux(tree->left, node_fd, ex, EX_WAIT);

	towait = ft_pid_pop(&(ex->pids));
	if (towait)
	{
		ft_close_pipes(ex->pipes);
		waitpid(towait->pid, &err_code, 0);
		ft_signal_state(SIGHANDLER_INT);
		// ft_printf("[EXEC] : OR waiting for pid [%d] at <%p>\n", towait->pid, towait);
		err_code = WEXITSTATUS(err_code);
	}
	else
		err_code = g_exit_code;
	free(towait);
	if (err_code != ERR_NOERRS)
	{
		// ft_printf("[EXEC] : OR branching right to <%p> \n[%d]->[%d]\n", tree->right, node_fd[0], node_fd[1]);
		ft_exec_mux(tree->right, node_fd, ex, EX_WAIT);
		towait = ft_pid_pop(&(ex->pids));
		if (towait)
		{
			ft_close_pipes(ex->pipes);
			waitpid(towait->pid, &err_code, 0);
			ft_signal_state(SIGHANDLER_INT);
			// ft_printf("[EXEC] : OR waiting for pid [%d] at <%p>\n", towait->pid, towait);
			err_code = WEXITSTATUS(err_code);
		}
		else
			err_code = g_exit_code;
		free(towait);
	}
}
