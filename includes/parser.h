/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:23:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/01 15:59:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* UTILS ******************************************************************** */

/**
 * @brief			Get prompt total string.
 * 
 * @param envp		Linked list.
 * 
 * @return			Formatted total prompt string.
*/
char	*ft_get_prompt_string(t_envvar *envp);

void	ft_print_logo(t_envvar *env);

/* STRING MANIPULATION ****************************************************** */

/**
 * @brief			Checks if quoting is respected.
 * 
 * @param str		String to check.
 * @param oldqs		Carried quote state.
 * 
 * @return			Final quoted string.
*/
char	*ft_quote_checker(char *str, t_quote_state qs);

/**
 * @brief			Recursively replace $VARS by their values.
 * 
 * @param vars		Linked list.
 * @param str		String to format.
 * @param qs		Carried quote state.
*/
char	*ft_replace_vars(t_envvar *vars, char *str, t_quote_state qs);

/**
 * @brief			Insert environment variable into a string.
 * 
 * @param vars		Linked list.
 * @param result	Actual result string.
 * @param str		String leftovers.
 * @param len		Len pointer (filled with inserted string len).
*/
char	*ft_insert_var(t_envvar *vars, char *result, char *str, int *len);

/**
 * @brief			Check if a string starts by a token, if yes fill
 * 					the token pointer.
 * 
 * @param str		String to analyze.
 * 
 * @return			1 if the string is headed by a token, 0 otherwise
*/
int		ft_is_token(char *str, t_quote_state qs);

#endif