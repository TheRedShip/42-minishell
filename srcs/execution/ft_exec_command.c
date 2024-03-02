/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:45:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/02 22:25:01 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_process_redirs(t_command *cmd, int *node_fd)
{
	int	fds[2];

	fds[0] = node_fd[0];
	fds[1] = node_fd[1];
	if (cmd->infile != STDIN_FILENO)
		fds[0] = cmd->infile;
	if (cmd->outfile != STDOUT_FILENO)
		fds[1] = cmd->outfile;
	if (fds[0] != STDIN_FILENO)
		dup2(fds[0], STDIN_FILENO);
	if (fds[1] != STDOUT_FILENO)
		dup2(fds[1], STDOUT_FILENO);
	ft_close_command(cmd);
}

void	ft_fake_pid_child(int err_code, t_command *cmd, t_executer *ex)
{
	pid_t	child;

	ft_signal_state(SIGHANDLER_IGN);
	child = fork();
	if (child == 0)
	{
		ft_close_command(cmd);
		ft_fork_exit(ex);
		exit(err_code);
	}
	ft_signal_state(SIGHANDLER_INT);
	ft_pid_push(&(ex->pids), ft_init_pid(child));
}

void	ft_exec_cmd(t_command *cmd, int *node_fd, t_executer *ex)
{
	char	**env;
	pid_t	child;

	ft_signal_state(SIGHANDLER_IGN);
	child = fork();
	if (child == 0)
	{
		env = ft_get_var_strs(*(cmd->envp), 0);
		ft_process_redirs(cmd, node_fd);
		ft_close_pipes(ex->pipes);
		execve(cmd->path, cmd->args, env);
	}
	ft_signal_state(SIGHANDLER_INT);
	ft_close_command(cmd);
	ft_pid_push(&(ex->pids), ft_init_pid(child));
}

void	ft_pipe_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex)
{
	pid_t	child;
	int		ret;

	ft_signal_state(SIGHANDLER_IGN);
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
	ft_signal_state(SIGHANDLER_INT);
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

void	ft_command_exit(int err_code)
{
	if (!WIFEXITED(err_code) && WCOREDUMP(err_code))
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		g_exit_code = 131;
	}
	if (WTERMSIG(err_code) == 2)
	{
		ft_dprintf(2, "\n");
		g_exit_code = 130;
	}
}

char	*ft_backtrim(char *str, char c)
{
	char	*tmp;
	char	*chr;

	chr = ft_strrchr(str, c);
	tmp = NULL;
	if (chr && *chr && *(chr + 1))
		tmp = ft_strndup(chr + 1, ft_strlen(str) - (chr - str));
	return (tmp);
}
