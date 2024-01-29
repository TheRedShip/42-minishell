/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:23:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/29 15:49:03 by rgramati         ###   ########.fr       */
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

// (( cat Make"fil"|wc>    '   outfile') || echo -n"n"n -nnnn fai"led") && sleep 1
// 1 1000100001000010011111100000000000111 100001001010100000100000000111 100000101
// 1110001000010000100111111000000000001111100001001000100000100010000111010000010

#endif