/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/08 16:17:05 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

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

#endif