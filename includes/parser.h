/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:23:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/29 21:32:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/**
 * @brief				Check if a string starts by a token, if yes fill
 * 						the token pointer.
 * 
 * @param str			String to analyze.
 * 
 * @return				1 if the string is headed by a token, 0 otherwise
*/
int	ft_is_token(char *str, t_quote_state qs);

#endif