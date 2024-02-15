/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/15 19:57:17 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

/* TYPEDEFS ***************************************************************** */

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
 * @struct			s_pipes.
 * @brief			Pipe Stack (LIFO).
 * 
 * @param fd		(int[2])		Pipe array.
 * @param next		(next)			Previous pipe.
*/
typedef struct s_pipes
{
	int				fd[2];
	t_pid			*waitlist;
	struct s_pipes	*next;
}	t_pipes;

/**
 * @struct			s_executor.
 * @brief			Execution data, carried during tree reading.
 * 
 * @param input		(int)			Input file descriptor.
 * @param output	(int)			Output file descriptor.
 * @param pipes		(t_pipes *)		Pipe stack.
 * @param pids		(t_node *)		PID .
 */
typedef struct s_executor
{
	int		input;
	int		output;
	t_pipes	*pipes;
	t_node	*root;
}	t_executor;

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
 * @param p			t_pipes pointer.
*/
void		ft_del_pipe(t_pipes *p);

/* S_EXECUTOR *************************************************************** */

/**
 * @brief			Initializes a new t_executor.
 * 
 * @return			A pointer to the newly allocated t_executor.
*/
t_executor	*ft_init_executor();

/* EXECUTION **************************************************************** */

/**
 * @brief			Execution dispatcher, called for every t_node.
 * 
 * @param tree		Actual t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec(t_node *tree, t_executor *ex);

/**
 * @brief			Process redirections for a COMMAND t_node.
 * 
 * @param cmd		Actual COMMAND t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_process_redirs(t_command *cmd, t_executor *ex);

/**
 * @brief			Execute an OR t_node.
 * 
 * @param tree		Actual OR t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec_or(t_node *tree, t_executor *ex);

/**
 * @brief			Execute an AND t_node.
 * 
 * @param tree		Actual AND t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec_and(t_node *tree, t_executor *ex);

/**
 * @brief			Execute a COMMAND t_node
 * 
 * @param tree		Actual COMMAND t_node.
 * @param ex		t_executor carried data for execution.
*/
void		ft_exec_command(t_node *tree, t_executor *ex);

/* FILE MANAGEMENT ********************************************************** */


void		ft_close_v(int nb, int fd, ...);

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

/**
 * @brief			Close a t_command's fd.
 * 
 * @param tree		t_node with command inside.
*/
void		ft_close_command(t_node *tree);

/**
 * @brief			Close all fds in a tree recursively.
 * 
 * @param tree		t_node tree to close.
*/
void		ft_close_tree_rec(t_node *tree);

/**
 * @brief			Close t_executor
 * 
 * @param ex		t_executor to close.
*/
void		ft_close_executor(t_executor *ex);

#endif