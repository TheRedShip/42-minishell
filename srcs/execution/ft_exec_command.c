/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:45:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 22:21:31 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_connect_input(t_command *cmd, int hd_last)
{
	if (hd_last)
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		cmd->infile = cmd->heredoc;
	}
	else
	{
		if (cmd->heredoc > 2)
			close(cmd->heredoc);
	}
}

void	ft_exec_cmd(t_command *cmd, int *node_fd, t_executer *ex)
{
	char	**env;
	pid_t	child;

	child = fork();
	if (child == -1)
		return ;
	if (child == 0)
	{
		env = ft_get_var_strs(*(cmd->envp), 0);
		ft_process_redirs(cmd, node_fd);
		ft_close_pipes(ex->pipes);
		ft_close_tree_rec(ft_tree_holder(0, NULL));
		execve(cmd->path, cmd->args, env);
	}
	ft_close_command(cmd);
	ft_pid_push(&(ex->pids), ft_init_pid(child));
}

t_error	ft_command_startup(t_command *cmd, t_executer *ex)
{
	int	hd_last;

	hd_last = 0;
	if (ft_command_updater(cmd))
	{
		ft_fake_pid_child(0, ex);
		return (ERR_NOTCMD);
	}
	if (ft_open_outputs(cmd) || ft_open_inputs(cmd, &hd_last))
	{
		ft_fake_pid_child(1, ex);
		return (ERR_FAILED);
	}
	ft_connect_input(cmd, hd_last);
	if (!cmd->path && cmd->redirs)
	{
		ft_fake_pid_child(0, ex);
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

t_error	ft_command_checker(t_command *cmd, t_executer *ex)
{
	struct stat	stat_s;

	if (access(cmd->path, F_OK))
		return (ERR_NOERRS);
	stat(cmd->path, &stat_s);
	if (!S_ISREG(stat_s.st_mode))
	{
		if (S_ISFIFO(stat_s.st_mode))
			ft_error_message(ERR_NOPERM, cmd->path);
		else if (S_ISDIR(stat_s.st_mode))
			ft_error_message(ERR_ISADIR, cmd->path);
		ft_fake_pid_child(126, ex);
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

void	ft_cmd_handler(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	char		*err_str;
	t_command	*cmd;

	err_str = NULL;
	cmd = tree->command;
	if (ft_command_startup(cmd, ex) || ft_command_checker(cmd, ex))
		return ;
	if (!ft_builtin(cmd, node_fd, ex, mode))
		return ;
	if (access(cmd->path, F_OK))
	{
		ft_fake_pid_child(127, ex);
		if (cmd->args && *cmd->args)
			err_str = *cmd->args;
		ft_error_message(ERR_NOTCMD, err_str);
		return ;
	}
	ft_exec_cmd(cmd, node_fd, ex);
}
