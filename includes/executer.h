/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/25 18:56:34 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

/* S_PID ******************************************************************** */

/**
 * @brief			Initializes a new t_pid.
 * 
 * @param pid		PID to set, NULL most times.
 * 
 * @return			A pointer to the newly allocated t_pid.
*/
t_pid		*ft_init_pid(pid_t pid);

/**
 * @brief			Pushes a t_pid into a t_pid stack.
 * 
 * @param head		Stack head adress.
 * @param top		t_pid to push in.
*/
void		ft_pid_push(t_pid **head, t_pid *top);

/**
 * @brief			Pop a t_pid from a t_pid stack and returns it.
 * 
 * @param head		Stack head adress.
 * 
 * @return			Popped t_pid.
*/
t_pid		*ft_pid_pop(t_pid **head);

/**
 * @brief			De-allocate a t_pid stack.
 * 
 * @param p_list	t_pid stack.
*/
void		ft_del_pid_list(t_pid *p_list);

/* S_PIPES ****************************************************************** */

/**
 * @brief			Initializes a new t_pipes.
 * 
 * @return			A pointer to the newly allocated t_pipes.
*/
t_pipes		*ft_init_pipes(void);

/**
 * @brief			Pushes a t_pipes into a t_pipes stack.
 * 
 * @param head		Stack head adress.
 * @param top		t_pipes to push in.
*/
void		ft_pipes_push(t_pipes **head, t_pipes *top);

/**
 * @brief			Pop a t_pipes from a t_pipes stack and returns it.
 * 
 * @param head		Stack head adress.
 * 
 * @return			Popped t_pipes.
*/
t_pipes		*ft_pipes_pop(t_pipes **head);

/**
 * @brief			De-allocate a t_pipes, closing file descriptors, and call
 * 					ft_del_pid_list on waitlist attribute.
 * 
 * @param p			t_pipes to free.
*/
void		ft_del_pipe(t_pipes *p);

/* S_EXECUTOR *************************************************************** */

/**
 * @brief			Initializes a new t_executor.
 * 
 * @return			A pointer to the newly allocated t_executor.
*/
t_executor	*ft_init_executor(t_node *root);

/**
 * @brief			De-allocate a t_executor, calling ft_del_pipe on pipes
 * 					attribute if not NULL.
 * 
 * @param ex		t_executor to free.
*/
void		ft_del_executor(t_executor *ex);

/* EXECUTION **************************************************************** */

/**
 * @brief			Execution dispatcher, called for every t_node.
 * 
 * @param tree		Actual t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec(t_node *tree, t_executor *ex, t_exec_status status);

/**
 * @brief			Process redirections for a COMMAND t_node.
 * 
 * @param cmd		Actual COMMAND t_node.
 * @param ex		t_executor carried data for execution.
*/
int			ft_process_redirs(t_command *cmd, t_executor *ex);

/**
 * @brief			Process redirections for a builtin COMMAND t_node.
 * 
 * @param cmd		Actual COMMAND t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_process_bredirs(t_command *cmd, t_executor *ex, int *tmps);

/**
 * @brief			Execute an OR t_node.
 * 
 * @param tree		Actual OR t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec_or(t_node *tree, t_executor *ex, t_exec_status status);

/**
 * @brief			Execute an AND t_node.
 * 
 * @param tree		Actual AND t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec_and(t_node *tree, t_executor *ex, t_exec_status status);

/**
 * @brief			Startup for a COMMAND t_node execution
 * 
 * @param tree		Actual COMMAND t_node.
 * @param ex		t_executor carried data for execution.
 * 
 * @return			ERR_FAILED in case of errors, ERR_NOTCMD if not a builtin
 * 					ERR_NOERRS if it was a builtin.
*/
int			ft_cmd_start(t_node *tree, t_executor *ex, int *b_fds);

void		ft_exec_command(t_node *tree, t_executor *ex, t_exec_status status);

/**
 * @brief			Try to fetch builtin commands.
 * 
 * @param command	t_command to test.
 * 
 * @return			ERR_NOERRS if it did execute a builtin, ERR_FAILED otherwise.
*/
int			ft_exec_builtins(t_command *cmd, t_executor *ex, int *btemps);

/* FILE MANAGEMENT ********************************************************** */



/* UTILS ******************************************************************** */

void		ft_command_checker(t_command *cmd);

#endif