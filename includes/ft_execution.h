/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 18:03:10 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

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

t_error	ft_builtin(t_command *cmd, int *fd, t_executer *ex, t_mode mode);

t_error	ft_command_startup(t_command *cmd, t_executer *ex);

t_error	ft_command_updater(t_command *cmd);

t_error	ft_command_checker(t_command *cmd, t_executer *ex);

/* UTILS ******************************************************************** */

void			ft_args_updater(t_command *cmd);

void			ft_path_updater(t_command *cmd);

void	ft_fake_pid_child(int err_code, t_executer *ex);

void	ft_process_redirs(t_command *cmd, int *node_fd);

#endif