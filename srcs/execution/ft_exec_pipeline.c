/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:04:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 20:55:24 by rgramati         ###   ########.fr       */
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
	else if (tree->token)
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
	if (errno == EMFILE)
	{
		g_exit_code = 1;
		ft_error_message(ERR_INVFDS, "pipe");
		return ;
	}
}

void	ft_wait_pipeline(t_pid *tmp, t_executer *ex, t_mode mode)
{
	t_pid	*towait;
	int		err_code;
	int		first;

	first = 0;
	ft_del_pipe(ft_pipes_pop(&(ex->pipes)));
	while (mode == EX_WAIT && ex->pids && ex->pids != tmp)
	{
		towait = ft_pid_pop(&(ex->pids));
		waitpid(towait->pid, &err_code, 0);
		ft_command_exit(err_code);
		if (!first++)
			g_exit_code = WEXITSTATUS(err_code);
		free(towait);
	}
}

void	ft_exec_pipe(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	int		fds[2];
	t_pid	*tmp;
	t_pipes	*tmp_pipe;

	tmp = NULL;
	if (mode == EX_WAIT)
		tmp = ex->pids;
	tmp_pipe = ex->pipes;
	ft_pipes_push(&(ex->pipes), ft_init_pipes());
	if (ex->pipes == tmp_pipe)
		return ;
	if (ex->pipes->fd[0] == -1 || ex->pipes->fd[1] == -1)
		return ;
	fds[0] = node_fd[0];
	fds[1] = ex->pipes->fd[1];
	ft_exec_mux(tree->left, (int *) fds, ex, EX_PIPE);
	fds[0] = ex->pipes->fd[0];
	fds[1] = node_fd[1];
	ft_exec_mux(tree->right, (int *) fds, ex, EX_PIPE);
	ft_wait_pipeline(tmp, ex, mode);
}

void	ft_and_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	pid_t	child;
	int		err_code;

	err_code = 0;
	if (mode == EX_PIPE)
	{
		child = fork();
		if (child == -1)
			return ;
		if (child == 0)
		{
			err_code = ft_exec_and(tree, node_fd, ex);
			ft_fork_exit(ex);
			exit(err_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
	}
	else
		ft_exec_and(tree, node_fd, ex);
}

void	ft_or_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	pid_t	child;
	int		err_code;

	err_code = 0;
	if (mode == EX_PIPE)
	{
		child = fork();
		if (child == -1)
			return ;
		if (child == 0)
		{
			err_code = ft_exec_or(tree, node_fd, ex);
			ft_fork_exit(ex);
			exit(err_code);
		}
		ft_pid_push(&(ex->pids), ft_init_pid(child));
	}
	else
		ft_exec_or(tree, node_fd, ex);
}
