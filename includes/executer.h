/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 14:59:47 by rgramati         ###   ########.fr       */
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
 * @brief			De-allocate a t_pipes, closing file descriptors
 * 
 * @param p			t_pipes to free.
*/
void		ft_del_pipe(t_pipes *p);

/* EXECUTION **************************************************************** */

void	ft_exec_mux(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

void	ft_exec_pipe(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

void	ft_and_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

void	ft_exec_and(t_node *tree, int *node_fd, t_executer *ex);

void	ft_or_divider(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

void	ft_exec_or(t_node *tree, int *node_fd, t_executer *ex);

void	ft_cmd_handler(t_node *tree, int *node_fd, t_executer *ex, t_mode mode);

void	ft_exec_cmd(t_command *cmd, int *node_fd, t_executer *ex);

void	ft_command_exit(int err_code);

void	ft_pipe_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex);

void	ft_wait_builtin(int (*f)(t_command *), t_command *cmd, t_executer *ex);

t_error_code	ft_builtin_handler(t_command *cmd, int *node_fd, t_executer *ex, t_mode mode);

t_error_code	ft_command_startup(t_command *cmd, t_executer *ex);

t_error_code	ft_command_updater(t_command *cmd);

t_error_code	ft_command_checker(t_command *cmd, t_executer *ex);

/* UTILS ******************************************************************** */

void			ft_args_updater(t_command *cmd);

void			ft_path_updater(t_command *cmd);

void	ft_fake_pid_child(int err_code, t_command *cmd, t_executer *ex);

void	ft_process_redirs(t_command *cmd, int *node_fd);

#endif