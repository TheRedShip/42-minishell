/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:04:23 by rgramati          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/01 18:15:19 by ycontre          ###   ########.fr       */
=======
/*   Updated: 2024/03/01 17:44:57 by rgramati         ###   ########.fr       */
>>>>>>> ec2e8cd14de25d56159a5103494cc6151a70098c
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
	int		err_code;
	int		fds[2];
	t_pid	*tmp;
	t_pid	*test;
	t_pipes	*test2;

	if (mode == EX_WAIT)
		tmp = ex->pids;
	ft_pipes_push(&(ex->pipes), ft_init_pipes());
	pipe(ex->pipes->fd);
	fds[0] = node_fd[0];
	fds[1] = ex->pipes->fd[1];
	ft_exec_mux(tree->left, (int *) fds, ex, EX_PIPE);
	fds[0] = ex->pipes->fd[0];
	fds[1] = node_fd[1];
	ft_exec_mux(tree->right, (int *) fds, ex, EX_PIPE);
	test2 = ft_pipes_pop(&(ex->pipes));
	ft_del_pipe(test2);
	while (mode == EX_WAIT && ex->pids && ex->pids != tmp)
	{
		test = ft_pid_pop(&(ex->pids));
		waitpid(test->pid, &err_code, 0);
		ft_command_exit(err_code);
		free(test);
	}
}

void	ft_and_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	pid_t	child;

	ft_printf("\n[EXEC] : AND encountered\n");
	if (mode == EX_PIPE)
	{
		child = fork();
		if (child == 0)
		{
			ft_exec_and(tree, node_fd, ex);
			ft_fork_exit(ex);
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
	pid_t	child;

	ft_printf("\n[EXEC] : OR encountered\n");
	if (mode == EX_PIPE)
	{
		child = fork();
		if (child == 0)
		{
			ft_exec_or(tree, node_fd, ex);
			ft_fork_exit(ex);
			exit(g_exit_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
		ft_printf(": pushed pid <%p> [pid=%d]\n", ex->pids, ex->pids->pid);
	}
	else
		ft_exec_or(tree, node_fd, ex);
}
