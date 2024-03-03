/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:50:05 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 14:50:26 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex)
{
	pid_t	child;
	int		ret;

	child = fork();
	if (child == 0)
	{
		if (f == &ft_exit)
		{
			ft_close_executer(ex);
			free(ex);
			ex = NULL;
		}
		ret = f(cmd);
		ft_close_executer(ex);
		ft_close_command(cmd);
		free(ex);
		ex = NULL;
		if (f != &ft_exit)
			ft_fork_exit(ex);
		exit(ret);
	}
	ft_close_command(cmd);
	ft_pid_push(&(ex->pids), ft_init_pid(child));
}

void	ft_wait_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex)
{
	if (f == &ft_exit && ft_tab_len(cmd->args) <= 2)
	{
		ft_close_executer(ex);
		free(ex);
		ft_dprintf(2, "exit\n");
	}
	int weshh = f(cmd);
	ft_fake_pid_child(weshh, cmd, ex);
	ft_close_command(cmd);
}

t_error_code	ft_builtin_handler(t_command *cmd, int *node_fd, t_executer *ex, t_mode mode)
{
	char		*trim;
	char		**tmp;
	static int	(*builtins[7])(t_command *) = \
	{&ft_cd, &ft_pwd, &ft_echo, &ft_env, &ft_export, &ft_unset, &ft_exit};
	static char	*builtins_str[8] = \
	{"cd", "pwd", "echo", "env", "export", "unset", "exit", NULL};

	tmp = builtins_str;
	trim = ft_backtrim(cmd->path, '/');
	while (*tmp && ft_strncmp(*tmp, trim, ft_strlen(*tmp) + 1))
		tmp++;
	free(trim);
	if (!*tmp)
		return (ERR_ERRORS);
	if (cmd->infile == STDIN_FILENO && node_fd[0] != STDIN_FILENO)
		cmd->infile = node_fd[0];
	if (cmd->outfile == STDOUT_FILENO && node_fd[1] != STDOUT_FILENO)
		cmd->outfile = node_fd[1];
	if (mode == EX_PIPE)
		ft_pipe_builtin(builtins[tmp - builtins_str], cmd, ex);
	else
		ft_wait_builtin(builtins[tmp - builtins_str], cmd, ex);
	return (ERR_NOERRS);
}