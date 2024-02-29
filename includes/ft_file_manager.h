/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:02:22 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/28 15:59:17 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_MANAGER_H
# define FT_FILE_MANAGER_H

/**
 * @brief			Get heredoc file descriptor.
 * 
 * @param delim		Heredoc delimiter.
 * @param hd_file	Temporary file name.
 * @param root		Root of the binary tree.
 * 
 * @return			Heredoc file descriptor, -1 if failed.
*/
int				ft_get_heredoc(char *delim, char *hd_file, t_node *root);

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

#endif