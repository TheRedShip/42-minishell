/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:54 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/23 21:36:53 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

/**
 * @enum			e_token_type
 * @brief			Token type.
 */
typedef enum e_token_type
{
	TK_BRACE = 0,
	TK_BINOP,
	TK_PIPES,
	TK_REDIR,
	TK_UNKNO
}   t_token_type;

/**
 * @enum			e_quote_state
 * @brief			Quote state.
 */
typedef enum e_quote_state
{
	QU_ZERO = 0,
	QU_SINGLE,
	QU_DOUBLE
}	t_quote_state;


/**
 * @struct			s_envvar
 * @brief			Environment variable linked list node.
 * 
 * @param name		Variable name
 * @param values	Variable values
 */
typedef struct s_envvar
{
	char			*name;
	char			**values;
	struct s_envvar	*next;
}	t_envvar;

/**
 * @struct			s_token
 * @brief			Command line token.
 * 
 * @param str		Token raw string;
 * @param type		Token type (see enum t_token_type)
 */
typedef struct s_token
{
	char            *str;
	t_token_type    type;
}   t_token;

/**
 * @struct			s_command
 * @brief			Command descriptor.
 * 
 * @param infile	Input file descriptor
 * @param outfile	Output file descriptor
 * @param path		Command path
 * @param args		Command arguments
 * @param envp		Command environment
 */
typedef struct s_command
{
	int				infile;
	int				outfile;
	char			*path;
	char			**args;
	char			**envp;
}   t_command;

/**
 * @struct			Environment variable structure
 * @brief			Environment variable linked list node.
 * 
 * @param rank		Node rank	
 * @param element	Node element (t_token || t_command)
 * @param left		Left child node
 * @param right		Right child node
 */
typedef struct s_node
{
	int					rank;
	void				*element;
	struct s_token_node *left;
	struct s_token_node *right;
}	t_node;

#endif