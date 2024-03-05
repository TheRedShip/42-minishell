/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:02:22 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 22:21:04 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_MANAGER_H
# define FT_FILE_MANAGER_H

/* FILE MANAGEMENT ********************************************************** */

/**
 * @brief			Get a temporary filename.
 * 
 * @param head		Start of the filename.
 * 					(consider always using "." starting names)
 * @param size		Number of random characters.
 * 
 * @return			Temporary filename allocated string.
*/
char		*ft_get_temp_file(char *head, int size);

/**
 * @brief			Manage heredoc opening.
 * 
 * @param tree		Tree pointer.
 * 
 * @return			ERR_FAILED if ^C in any heredoc, ERR_NOERRS otherwise.
*/
t_error		ft_heredoc_opening(t_node *tree);

/**
 * @brief			Opens recursively all heredocs in a tree.
 * 
 * @param nd		Node to open.
 * @param hd		Pointer to the failed heredoc boolean.
 * 
 * @return			ERR_HDSTOP in case of error, ERR_NOERRS otherwise.
*/
t_error		ft_manage_heredocs(t_node *nd, int *hd);

/**
 * @brief			Open heredocs for one command.
 * 
 * @param cmd		t_command pointer.
 * 
 * @return			ERR_HDSTOP in case of error, ERR_NOERRS otherwise.
*/
t_error		ft_open_heredocs(t_command *cmd);

/**
 * @brief			Open a file.
 * 
 * @param cmd		t_command to fill.
 * @param file		Pathname.
 * @param mode		Opening mode.
 * 
 * @return			ERR_INVFDS if fd error, ERR_AMBRED if ambiguous redirection
 * 					ERR_NOERRS otherwise.
*/
t_error		ft_open_file(t_command *cmd, char *file, int mode);

/**
 * @brief			Open output files for one command.
 * 
 * @param cmd		t_command pointer.
 * 
 * @return			ERR_FAILED in case of error, ERR_NOERRS otherwise.
*/
t_error		ft_open_outputs(t_command *cmd);

/**
 * @brief			Open input files for one command.
 * 
 * @param cmd		t_command pointer.
 * @param hd_last	heredoc last boolean.
 * 
 * @return			ERR_FAILED in case of error, ERR_NOERRS otherwise.
*/
t_error		ft_open_inputs(t_command *cmd, int *hd_last);

/* HEREDOC ****************************************************************** */

/**
 * @brief			Get heredoc file descriptor.
 * 
 * @param delim		Heredoc delimiter.
 * @param hd_file	Temporary file name.
 * 
 * @return			Heredoc file descriptor, -1 if failed.
*/
int			ft_get_heredoc(char *delim, char *hd_file);

/**
 * @brief			Manage return code from heredoc fork.
 * 
 * @param delim		Delimiter string pointer.
 * @param hd_file	File name string pointer.
 * @param err_code	Exit status from fork.
*/
int			ft_heredoc_exit(char *delim, char *hd_file, int err_code);

/**
 * @brief			Line up all heredoc lines and manage memory from fork.
 * 
 * @param delim		Delimiter string pointer.
 * @param hd_file	File name string pointer.
 * @param hd_fd		Heredoc file descriptor.
*/
int			ft_heredoc_line(char *delim, char *hd_file, int hd_fd);

/**
 * @brief			Parse one heredoc line
 * 
 * @param line		Line string adress.
 * @param hd_fd		Heredoc file descriptor.
 * @param exp		Expansion boolean.
*/
void		ft_parse_line(char **line, int hd_fd, int exp);

/**
 * @brief			Exit minishell if more than 16 heredocs.
 * 
 * @param tokens	Token linked list.
 * @param envp		Environment linked list adress.
*/
void		ft_heredoc_limit(t_token *tokens, t_envvar **envp);

/* CLOSE ******************************************************************** */

/**
 * @brief			Variadic close.
 * 
 * @param nb		How many files to close.
 * @param fd		First fd, then vararg.
*/
void		ft_close_v(int nb, int fd, ...);

/**
 * @brief			Close a t_command's fd.
 * 
 * @param command	t_command to close.
*/
void		ft_close_command(t_command *command);

/**
 * @brief			Close all fds in a tree recursively.
 * 
 * @param tree		t_node tree to close.
*/
void		ft_close_tree_rec(t_node *tree);

/**
 * @brief			Close all fds from a t_executer.
 * 
 * @param ex		t_executer to close.
*/
void		ft_close_executer(t_executer *ex);

/**
 * @brief			Close a pipe.
 * 
 * @param tmp_pipe	Pipe to close.
*/
void		ft_close_pipes(t_pipes *tmp_pipe);

/**
 * @brief			Exit a fork.
 * 
 * @param ex		Current t_executer.
*/
void		ft_fork_exit(t_executer *ex);

/* ************************************************************************** */

#endif