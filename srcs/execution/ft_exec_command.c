/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:45:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 14:50:55 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_exec_cmd(t_command *cmd, int *node_fd, t_executer *ex)
{
	char	**env;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		env = ft_get_var_strs(*(cmd->envp), 0);
		ft_process_redirs(cmd, node_fd);
		ft_close_pipes(ex->pipes);
		execve(cmd->path, cmd->args, env);
	}
	ft_close_command(cmd);
	ft_pid_push(&(ex->pids), ft_init_pid(child));
}

t_error_code	ft_command_startup(t_command *cmd, t_executer *ex)
{
	if (ft_command_updater(cmd))
	{
		ft_fake_pid_child(0, cmd, ex);
		return (ERR_NOTCMD);
	}
	if (ft_open_outputs(cmd) || ft_open_inputs(cmd))
	{
		ft_fake_pid_child(1, cmd, ex);
		return (ERR_FAILED);
	}
	if (!cmd->path && cmd->redirs)
	{
		ft_fake_pid_child(0, cmd, ex);
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

t_error_code	ft_command_checker(t_command *cmd, t_executer *ex)
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
		ft_fake_pid_child(126, cmd, ex);
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}
