/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/01 17:23:51 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// extern int	g_exit_code;

// void	ft_command_error(char **env, t_command *cmd, t_executor *ex)
// {
// 	ft_free_tab((void **)env);
// 	ft_clear_env(*(cmd->envp));
// 	ft_clear_tree(ex->root);
// 	ft_del_executor(ex);
// }

// void	start_execve(t_command *cmd, t_exec_status status)
// {
// 	char	**env;
// 	pid_t	pid;
// 	DIR		*file_check;

	// ft_signal_state(SIGHANDLER_IGN);
	
// 	if (pid == 0)
// 	{
// 		env = ft_get_var_strs(*(cmd->envp), 0);
// 		rl_clear_history();
// 		if (ft_process_redirs(cmd, ex) == ERR_ERRORS)
// 		{
// 			ft_command_error(env, cmd, ex);
// 			exit(ERR_FAILED);
// 		}
// 		file_check = opendir(cmd->path);
// 		if (errno != ENOTDIR)
// 		{
// 			ft_error_message(ERR_NOPERM, cmd->path);
// 			closedir(file_check);
// 			exit(126);
// 		}
// 		closedir(file_check);
// 		execve(cmd->path, cmd->args, env);
// 		perror("execve");
// 		exit(ERR_FAILED);
// 	}
// 	ft_signal_state(SIGHANDLER_INT);
// 	return (pid)
// }

// int	ft_cmd_start(t_node *tree, t_executor *ex, int *b_fds)
// {
// 	int		flags;
// 	char	*err_str;

// 	flags = 0b0000;
// 	err_str = NULL;
// 	ft_command_checker(tree->command);
// 	flags |= (tree->command->path && !*tree->command->path); // path = chaine vide 0b0001
// 	flags |= (ft_open_outputs(tree) || ft_open_inputs(tree)) << 1; // erreur douverture de fichiers 0b0010
// 	flags |= (!tree->command->path || access(tree->command->path, F_OK)) << 2; //pas de path ou pas acces au path 0b0100
// 	g_exit_code = (flags & 0b0010);
// 	if (flags & 0b0011)
// 		return (ERR_FAILED);
// 	if (flags & 0b0100)
// 		g_exit_code = 127;
// 	flags |= ft_exec_builtins(tree->command, b_fds) << 3; // builtin executed or not 0b1000
// 	if ((flags & 0b0100) && (flags & 0b1000))
// 	{
// 		if (tree->command->args && *tree->command->args)
// 			err_str = *tree->command->args;
// 		ft_error_message(ERR_NOTCMD, err_str);
// 		return (ERR_FAILED);
// 	}
// 	if (flags & 0b1000)
// 		return (ERR_NOTCMD);
// 	return (ERR_NOERRS);
// }

// int	ft_exec_builtins(t_command	*cmd, int *b_fds)
// {
// 	char		*trim;
// 	char		**tmp;
// 	static int	(*builtins[7])(t_command *) = \
// 	{&ft_cd, &ft_pwd, &ft_echo, &ft_env, &ft_export, &ft_unset, &ft_exit};
// 	static char	*builtins_str[8] = \
// 	{"cd", "pwd", "echo", "env", "export", "unset", "exit", NULL};
// }
