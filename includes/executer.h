/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/12 21:01:45 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

/* TYPEDEFS ***************************************************************** */

/**
 * @struct			s_pipes.
 * @brief			Pipe Stack (LIFO).
 * 
 * @param fd		(int[2])		Pipe array.
 * @param next		(next)			Previous pipe.
*/
typedef struct s_pipes
{
	int				fd[2];
	struct s_pipes	*next;
}	t_pipes;
 
/** 
 * @struct			s_pid.
 * @brief			PID Stack (LIFO).
 * 
 * @param pid		(pid_t)			PID.
 * @param next		(t_pid *)		Previous PID.
*/
typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

/**
 * @struct			s_executor.
 * @brief			Execution data, carried during tree reading.
 * 
 * @param input		(int)			Input file descriptor.
 * @param output	(int)			Output file descriptor.
 * @param pipes		(t_pipes *)		Pipe stack.
 * @param pids		(t_pid *)		PID stack.
 */
typedef struct s_executor
{
	int		input;
	int		output;
	t_pipes	*pipes;
	t_pid	*pids;
}	t_executor;

/* EXECUTION **************************************************************** */

void	ft_exec(t_node *root, t_node *tree, t_executor *ex);

void	ft_process_redirs(t_node *root, t_command *cmd, t_executor *ex);

void	ft_exec_or(t_node *root, t_node *tree, t_executor *ex);

void	ft_exec_and(t_node *root, t_node *tree, t_executor *ex);

void	ft_exec_command(t_node *root, t_node *tree, t_executor *ex);

/* FILE MANAGEMENT ********************************************************** */

/**
 * @brief			Manage input redirections.
 * 
 * @param tokens	Linked list loop pointer.
 * @param fd		Infile fd pointer for current command.
 * @param hd		Heredoc counter pointer.
 * 
 * @return			EC_FAILED if more than 16 heredocs, EC_SUCCES otherwise.
*/
int			ft_manage_inputs(t_token **tokens, int *fd, int *hd);

/**
 * @brief			Manage output redirections.
 * 
 * @param tokens	Linked list loop pointer.
 * @param fd		Outfile fd pointer for current command.
 * 
 * @return			EC_SUCCES.
*/
int			ft_manage_outputs(t_token **tokens, int *fd);

void	ft_close_command(t_node *tree);

void	ft_close_tree_rec(t_node *tree);

void	ft_close_files(t_node *root, t_executor *ex);

#endif