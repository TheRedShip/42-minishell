/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/04 23:51:09 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H

/* EXECUTION **************************************************************** */

/**
 * @brief			Execution multiplexer.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
 * @param mode		Execution mode.
*/
void	ft_exec_mux(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

/**
 * @brief			Execute a PIPE node.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
 * @param mode		Execution mode.
*/
void	ft_exec_pipe(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

/**
 * @brief			Divide AND execution, either forked or not.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
 * @param mode		Execution mode.
*/
void	ft_and_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

/**
 * @brief			Execute a AND node.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
*/
int		ft_exec_and(t_node *tree, int *node_fd, t_executer *ex);

/**
 * @brief			Divide OR execution, either forked or not.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
 * @param mode		Execution mode.
*/
void	ft_or_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

/**
 * @brief			Execute a OR node.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
*/
int		ft_exec_or(t_node *tree, int *node_fd, t_executer *ex);

/**
 * @brief			Command handler for execution.
 * 
 * @param tree		Node to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
 * @param mode		Execution mode.
*/
void	ft_cmd_handler(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

/**
 * @brief			Execute a t_command.
 * 
 * @param cmd		Command to execute.
 * @param node_fd	Fds for this node.
 * @param ex		Current t_executer.
*/
void	ft_exec_cmd(t_command *cmd, int *node_fd, t_executer *ex);

/**
 * @brief			Handle WTERMSIG and WCOREDUMP returns.
 * 
 * @param err_code	Return status to test.
*/
void	ft_command_exit(int err_code);

/**
 * @brief			Execute a builtin when mode is EX_PIPE.
 * 
 * @param f			Builtin function pointer.
 * @param cmd		t_command pointer with command metadata.
 * @param ex		Current t_executer.
*/
void	ft_pipe_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex);

/**
 * @brief			Execute a builtin when mode is EX_WAIT.
 * 
 * @param f			Builtin function pointer.
 * @param cmd		t_command pointer with command metadata.
 * @param ex		Current t_executer.
*/
void	ft_wait_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex);

/**
 * @brief			Handle builtin execution.
 * 
 * @param cmd		t_command to execute.
 * @param fd		File descriptors for builtins.
 * @param ex		Current t_executer.
 * @param mode		Execution mode.
 * 
 * @return			ERR_ERRORS if not a builtin cmd, ERR_NOERRS otherwise.
*/
t_error	ft_builtin(t_command *cmd, int *fd, t_executer *ex, t_mode mode);

/**
 * @brief			Error handling before executing (or not) a t_command.
 * 
 * @param cmd		t_command to analyze.
 * @param ex		Current t_executer.
 * 
 * @return			ERR_FAILED if something failed during startup, ERR_NOERRS
 * 					otherwise.
*/
t_error	ft_command_startup(t_command *cmd, t_executer *ex);

/**
 * @brief			Update command metadata.
 * 
 * @param cmd		t_command to update.
 * 
 * @return			ERR_NOTCMD if no path and no redirs, ERR_NOERRS otherwise.
*/
t_error	ft_command_updater(t_command *cmd);

/**
 * @brief			Check for bad permissions, or irreguar file execution.
 * 
 * @param cmd		t_command to check.
 * 
 * @return			ERR_FAILED if !S_ISREG, ERR_NOERRS otherwise.
 * 
*/
t_error	ft_command_checker(t_command *cmd, t_executer *ex);

/* UTILS ******************************************************************** */

/**
 * @brief			Updates t_command args.
 * 
 * @param cmd		t_command to update.
*/
void	ft_args_updater(t_command *cmd);

/**
 * @brief			Updates t_command path.
 * 
 * @param cmd		t_command to update.
*/
void	ft_path_updater(t_command *cmd);

/**
 * @brief			Updates t_command path.
 * 
 * @param cmd		t_command to update.
 * @param ex		Current t_executer.
*/
void	ft_fake_pid_child(int err_code, t_executer *ex);

/**
 * @brief			Process redirections for a fork.
 * 
 * @param cmd		t_command to redirect.
 * @param node_fd	Fds from t_node.
*/
void	ft_process_redirs(t_command *cmd, int *node_fd);

/* ************************************************************************** */

#endif