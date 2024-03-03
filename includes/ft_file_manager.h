/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:02:22 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 16:08:01 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_MANAGER_H
# define FT_FILE_MANAGER_H


/* FILE MANAGEMENT ********************************************************** */

t_error	ft_heredoc_opening(t_node *tree);

t_error	ft_manage_heredocs(t_node *nd, int *hd);

t_error	ft_open_heredocs(t_command *cmd);

void			ft_open_file(t_command *cmd, char *file, int mode);

t_error	ft_open_outputs(t_command *cmd);

t_error	ft_open_inputs(t_command *cmd);

/* HEREDOC ****************************************************************** */

/**
 * @brief			Get heredoc file descriptor.
 * 
 * @param delim		Heredoc delimiter.
 * @param hd_file	Temporary file name.
 * 
 * @return			Heredoc file descriptor, -1 if failed.
*/
int				ft_get_heredoc(char *delim, char *hd_file);

int				ft_heredoc_exit(char *delim, char *hd_file, int err_code);

int				ft_heredoc_line(char *delim, char *hd_file, int hd_fd);

void			ft_parse_line(char **line, int hd_fd, int exp);

void			ft_heredoc_limit(t_token *tokens, t_envvar **envp);

/* CLOSE ******************************************************************** */

/**
 * @brief			Variadic close.
 * 
 * @param nb		How many files to close.
 * @param fd		First fd, then vararg.
*/
void			ft_close_v(int nb, int fd, ...);

/**
 * @brief			Close a t_command's fd.
 * 
 * @param command	t_command to close.
*/
void			ft_close_command(t_command *command);

/**
 * @brief			Close all fds in a tree recursively.
 * 
 * @param tree		t_node tree to close.
*/
void			ft_close_tree_rec(t_node *tree);


void			ft_close_executer(t_executer *ex);

void			ft_close_pipes(t_pipes *tmp_pipe);

void			ft_fork_exit(t_executer *ex);

#endif