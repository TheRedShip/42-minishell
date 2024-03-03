/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:04:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 14:57:02 by rgramati         ###   ########.fr       */
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
	int		first;
	t_pid	*tmp;
	t_pid	*test;

	first = 0;
	if (mode == EX_WAIT)
		tmp = ex->pids;
	ft_pipes_push(&(ex->pipes), ft_init_pipes());
	fds[0] = node_fd[0];
	fds[1] = ex->pipes->fd[1];
	ft_exec_mux(tree->left, (int *) fds, ex, EX_PIPE);
	fds[0] = ex->pipes->fd[0];
	fds[1] = node_fd[1];
	ft_exec_mux(tree->right, (int *) fds, ex, EX_PIPE);
	ft_del_pipe(ft_pipes_pop(&(ex->pipes)));
	while (mode == EX_WAIT && ex->pids && ex->pids != tmp)
	{
		test = ft_pid_pop(&(ex->pids));
		waitpid(test->pid, &err_code, 0);
		ft_command_exit(err_code);
		if (!first++)
			g_exit_code = WEXITSTATUS(err_code);
		free(test);
	}
}

void	ft_and_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	pid_t	child;

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
	}
	else
		ft_exec_and(tree, node_fd, ex);
}

void	ft_or_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	pid_t	child;

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
	}
	else
		ft_exec_or(tree, node_fd, ex);
}

void	ft_cmd_handler(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	char	*err_str;

	err_str = NULL;
	if (ft_command_startup(tree->command, ex) || ft_command_checker(tree->command, ex))
		return ;
	if (!ft_builtin_handler(tree->command, node_fd, ex, mode))
		return ;
	if (access(tree->command->path, F_OK))
	{
		ft_fake_pid_child(127, tree->command, ex);
		if (tree->command->args && *tree->command->args)
			err_str = *tree->command->args;
		ft_error_message(ERR_NOTCMD, err_str);
		return ;
	}
	ft_exec_cmd(tree->command, node_fd, ex);
}
