/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:45:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/29 15:55:51 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_exec_cmd(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	(void) tree;
	(void) mode;
	(void) node_fd;
	(void) ex;

	ft_printf("\n[EXEC] : Executing command <%p>{path=\"%s\"} \n[%d]->[%d]\n", tree->command, tree->command->path, node_fd[0], node_fd[1]);
	ft_pid_push(&(ex->pids), ft_init_pid(0));
	ft_printf("[EXEC] : Command pushed pid <%p> [pid=%d]\n", ex->pids, ex->pids->pid);
}

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
}

void	ft_cmd_handler(t_node *tree, int *node_fd, t_executer *ex, t_mode mode)
{
	char	*err_str;

	err_str = NULL;
	ft_command_checker(tree->command);
	ft_display_command(tree->command);
	if (access(tree->command->path, F_OK))
	{
		g_exit_code = 127;
		if (tree->command->args && *tree->command->args)
			err_str = *tree->command->args;
		ft_error_message(ERR_NOTCMD, err_str);
		return ;
	}
	if (!ft_builtin_handler(tree->command))
		return ;
	ft_exec_cmd(tree, node_fd, ex, mode);
}

// t_error_code	ft_verify_command()
// {
	
// }

char	*ft_backtrim(char *str, char c)
{
	char	*tmp;
	char	*chr;

	chr = ft_strrchr(str, c);
	tmp = NULL;
	if (chr && *chr && *(chr + 1))
		tmp = ft_strndup(chr + 1 , ft_strlen(str) - (chr - str));
	return (tmp);
}

t_error_code	ft_builtin_handler(t_command *cmd)
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
	if (!tmp)
		return (ERR_ERRORS);
	g_exit_code = builtins[tmp - builtins_str](cmd);
	return (ERR_NOERRS);
}
