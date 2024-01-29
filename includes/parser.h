/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:23:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/29 15:46:03 by rgramati         ###   ########.fr       */
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
int	ft_is_token(char *str);

// (( cat Make"fil"|wc>    'outfile') || echo -n"n"n -nnnn fai"led") && sleep 1
// 1 1000100001000110011111000000000111 100001001010100000100010001111 10000010


// || echo -n"n"n -nnnn fai"led") && sleep 1

#endif