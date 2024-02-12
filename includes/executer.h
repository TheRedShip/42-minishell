/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/12 16:44:14 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

/* TYPEDEFS ***************************************************************** */

/**
 * @struct			s_envvar
 * @brief			Environment variable linked list node.
 * 
 * @param input		(int)			Input file descriptor.
 * @param output	(int)			Output file descriptor.
 * @param pipe_fd	(int[2])		Next element.
 */
typedef struct s_executor
{
	int	input;
	int	output;
	int	pipe_fd[2];
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