/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:45:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/01 18:37:52 by ycontre          ###   ########.fr       */
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
	ft_printf("[EXEC] : Command pushed pid <%p> [pid=%d]\n", \
		ex->pids, ex->pids->pid);
}

void	ft_exec_builtin(int (*f)(t_command *), t_command *cmd, t_mode mode)
{
	(void) mode;
	f(cmd);
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
	while (*tmp && ft_strncmp(*tmp, trim, ft_strlen(*tmp)))
		tmp++;
	free(trim);
	if (!*tmp)
		return (ERR_ERRORS);
	if (tmp - builtins_str == 6)
		free(ex);
	if (cmd->infile == STDIN_FILENO && node_fd[0] != STDIN_FILENO)
		cmd->infile = node_fd[0];
	if (cmd->outfile == STDOUT_FILENO && node_fd[1] != STDOUT_FILENO)
		cmd->outfile = node_fd[1];
	ft_exec_builtin(builtins[tmp - builtins_str], cmd, mode);
	return (ERR_NOERRS);
}

t_error_code	ft_command_startup(t_command *cmd)
{
	struct stat	stat_s;

	if (ft_command_updater(cmd))
	{
		g_exit_code = 0;
		return (ERR_NOTCMD);
	}
	if (ft_open_outputs(cmd) || ft_open_inputs(cmd))
	{
		g_exit_code = 1;
		return (ERR_FAILED);
	}
	if (access(cmd->path, F_OK))
		return (ERR_NOERRS);
	stat(cmd->path, &stat_s);
	if (!S_ISREG(stat_s.st_mode))
	{
		if (S_ISFIFO(stat_s.st_mode))
			ft_error_message(ERR_NOPERM, cmd->path);
		else if (S_ISDIR(stat_s.st_mode))
			ft_error_message(ERR_ISADIR, cmd->path);
		g_exit_code = 126;
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

void	ft_cmd_handler(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	char	*err_str;

	(void) mode;
	err_str = NULL;
	if (ft_command_startup(tree->command))
		return ;
	if (!ft_builtin_handler(tree->command, node_fd, ex, mode))
		return ;
	if (access(tree->command->path, F_OK))
	{
		g_exit_code = 127;
		if (tree->command->args && *tree->command->args)
			err_str = *tree->command->args;
		ft_error_message(ERR_NOTCMD, err_str);
		return ;
	}
	ft_exec_cmd(tree->command, node_fd, ex);
}

void	ft_command_exit(int err_code)
{
	g_exit_code = WEXITSTATUS(err_code);
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
