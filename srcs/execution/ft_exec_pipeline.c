/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:04:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/29 15:37:54 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

__always_inline
void	ft_exec_mux(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	if (!ex || !tree || !node_fd)
		return ;
	if (tree->command)
		ft_cmd_handler(tree, node_fd, ex, mode);
	else
	{
		if (tree->token->type & TK_BINOPS)
		{
			if (!ft_strncmp(tree->token->str, "&&", 3))
				ft_and_divider(tree, node_fd, ex, mode);
			else
				ft_or_divider(tree, node_fd, ex, mode);
		}
		else
			ft_exec_pipe(tree, node_fd, ex, mode);
	}
}

void	ft_exec_pipe(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	// int		err_code;
	int		fds[2];
	t_pid	*tmp;

	ft_printf("\n[EXEC] : Pipeline encoutered");
	if (mode == EX_WAIT)
	{
		tmp = ex->pids;
		ft_printf(" (START)");
	}
	ft_pipes_push(&(ex->pipes), ft_init_pipes());
	pipe(ex->pipes->fd);
	ft_printf(": <%p> pushed pipe \n[%d]->[%d]\n", ex->pipes, ex->pipes->fd[0], ex->pipes->fd[1]);

	fds[0] = node_fd[0];
	fds[1] = ex->pipes->fd[1];
	ft_printf("[EXEC] : <%p> pipe branching left to <%p>\n", ex->pipes, tree->left, fds[0], fds[1]);
	ft_exec_mux(tree->left, (int *) fds, ex, EX_PIPE);
	fds[0] = ex->pipes->fd[0];
	fds[1] = node_fd[1];
	ft_printf("[EXEC] : <%p> pipe branching right to <%p>\n", ex->pipes, tree->right, fds[0], fds[1]);
	ft_exec_mux(tree->right, (int *) fds, ex, EX_PIPE);
	
	if (mode == EX_WAIT)
	{
		while (ex->pids && ex->pids != tmp)
		{
			t_pid *test = ft_pid_pop(&(ex->pids));
			ft_printf("[EXEC] : <%p> pipe waiting for pid [%d] at <%p>\n", ex->pipes, test->pid, test);
			// waitpid(test->pid, &err_code, 0);
			free(test);
		}
	}
	t_pipes *test2 = ft_pipes_pop(&(ex->pipes));
	ft_printf("[EXEC] : <%p> Pipeline ended: closing pipe\n", test2);
	// g_exit_code = WEXITSTATUS(err_code);
	ft_del_pipe(test2);
}

void	ft_and_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	(void) tree;
	int		err_code = 0;
	pid_t	child;
	
	(void) err_code;
	ft_printf("\n[EXEC] : AND encountered\n");
	if (mode == EX_PIPE)
	{
		child = fork();
		if (child == 0)
		{
			ft_exec_and(tree, node_fd, ex);
			// FREE and close fds
			exit(g_exit_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
		ft_printf("[EXEC] : pushed pid <%p> [pid=%d]\n", ex->pids, ex->pids->pid);
	}
	else
		ft_exec_and(tree, node_fd, ex);
}

void	ft_or_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	(void) tree;
	int		err_code = 0;
	pid_t	child;

	(void) err_code;
	ft_printf("\n[EXEC] : AND encountered");
	if (mode == EX_PIPE)
	{
		child = fork();
		if (child == 0)
		{
			ft_exec_or(tree, node_fd, ex);
			// FREE and close fds
			exit(g_exit_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
		ft_printf(": pushed pid <%p> [pid=%d]\n", ex->pids, ex->pids->pid);
	}
	else
		ft_exec_or(tree, node_fd, ex);
}
