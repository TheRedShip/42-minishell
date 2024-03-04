/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enumerates.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:36:47 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/04 22:58:51 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENUMERATES_H
# define FT_ENUMERATES_H

/* ENUMS ******************************************************************** */

/**
 * @enum			e_token_type
 * @brief			Token type.
 */
typedef enum e_token_type
{
	TK_STRING = 0b00001,
	TK_BRACES = 0b00010,
	TK_BINOPS = 0b00100,
	TK_PIPEXS = 0b01000,
	TK_REDIRS = 0b10000
}	t_token_type;

/**
 * @enum			e_redir_type
 * @brief			Redirection type.
 */
typedef enum e_redir_type
{
	RD_INFILES,
	RD_HEREDOC,
	RD_OUTPUTS,
	RD_APPENDS
}	t_redir_type;

/**
 * @enum			e_quote_state
 * @brief			Quote state.
 */
typedef enum e_quote_state
{
	QU_ZERO = 0,
	QU_SINGLE,
	QU_DOUBLE,
	QU_IGNORE
}	t_qstate;

/**
 * @enum			e_exec_status.
 * @brief			Execution status.
 */
typedef enum e_mode
{
	EX_WAIT = 0,
	EX_PIPE = 1
}	t_mode;

/**
 * @enum			e_open_status.
 * @brief			File opening status.
 */
typedef enum e_open_status
{
	OP_HDOCKO = -3,
	OP_FILEHD,
	OP_FILEKO,
	OP_FILEOK,
	OP_FILEXX
}	t_open_status;

/**
 * @enum			e_handler_state
 * @brief			Handler state.
 */
typedef enum e_handler_state
{
	SIGHANDLER_IGN,
	SIGHANDLER_INT,
	SIGHANDLER_DQU,
	SIGHANDLER_H_D
}	t_handler_state;

/**
 * @enum			e_error_code
 * @brief			ERR return values.
 */
typedef enum e_error_code
{
	ERR_NOERRS,
	ERR_FAILED,
	ERR_ERRORS,
	ERR_NOTNUM,
	ERR_TMARGS,
	ERR_NOTSET,
	ERR_NOFORD,
	ERR_NOTVAL,
	ERR_HDSTOP,
	ERR_DQSTOP,
	ERR_NOTCMD,
	ERR_SYNTXQ,
	ERR_SYNTXT,
	ERR_HLIMIT,
	ERR_NOPERM,
	ERR_ISADIR,
	ERR_INVOPT,
	ERR_INVFDS,
	ERR_AMBRED
}	t_error;

/* ************************************************************************** */

#endif