/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:16:19 by marvin            #+#    #+#             */
/*   Updated: 2024/01/16 16:16:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <dirent.h>
# include "libft.h"

# include "data_structures.h"
# include "parser.h"
# include "builtins.h"
# include "executer.h"

# define MINI "minishell: "

# define P_SUCCESS "\001\033[30;102;1m\002$?\001\033[0m\002 "
# define P_FAIL "\001\033[30;101;1m\002$?\001\033[0m\002 "
# define P_TAIL "\001\033[30;47;3;1m\002[MinishellRC]:\001\033[0m\002 "

# define P_SDQUOTE "\001\033[30;106;1m\002''\001\033[0m\002 "
# define P_DDQUOTE "\001\033[30;104;1m\002\"\"\001\033[0m\002 "
# define P_ENDQUOTE "\001\033[30;47;3;1m\002/!\\  [dquote]:\001\033[0m\002 > "

# define P_HEREDOC "\001\033[30;105;1m\002HD\001\033[0m\002 "
# define P_HD_TAIL "\001\033[30;47;3;1m\002here-document:\001\033[0m\002 > "

# define P_ERROR "\001\033[30;47;1m\002!!\001\033[0m\002 "
# define P_ERR_TAIL "\001\033[37;41;1m\002[   ERROR!   ]\001\033[0m\002 > "

# define P_WARNING "\001\033[30;47;1m\002!!\001\033[0m\002 "
# define P_WNG_TAIL "\001\033[37;43;1m\002[  WARNING!  ]\001\033[0m\002 > "

# ifndef OPEN_READ
#  define OPEN_READ O_RDONLY
# endif

# ifndef OPEN_CREATE
#  define OPEN_CREATE O_WRONLY | O_TRUNC | O_CREAT
# endif

# ifndef OPEN_APPEND
#  define OPEN_APPEND O_WRONLY | O_CREAT | O_APPEND
# endif

# ifndef OPEN_EXCL
#  define OPEN_EXCL O_WRONLY | O_TRUNC | O_EXCL | O_CREAT
# endif

typedef enum e_handler_state
{
	SIGHANDLER_IGN,
	SIGHANDLER_INT,
	SIGHANDLER_DQU,
	SIGHANDLER_H_D
}	t_handler_state;

typedef enum e_error_code
{
	ERR_NOERRS = 0,
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
	ERR_SYNTAX,
}	t_error_code;

// typedef enum e_error
// {
// 	ERR_
// }

/**
 * @brief				Exit Handler.
 * 
 * @param exit_code		Exit code.
 * @param ec			Error code (see enum e_error_code).
 * @param cmd			t_command pointer with command meta-data.
 * @param prompt		Prompt line pointer.
*/
void	ft_exit_manager(int exit_code, int ec, t_command *cmd);

/* ************************************************************************** */
char	*ft_get_pwd(void);

int		ft_isnt_empty(char *str);

/* PARSING ****************************************************************** */
char	*parse_quotes(char *string);
// char	*parse_dollar(char *string, t_envvar *envp);
int		ft_qs_update(char c, t_quote_state *qs);
// char	*str_add(char *dest, char *src, size_t place);
// char	*str_append(char *str, char c);
// char	*str_add(char *dest, char *src, size_t place);
/* ************************************************************************** */

/* PROMPTING **************************************************************** */
void	ft_prompt_handle(t_envvar **envp);

void	ft_prompt_tokenization(char *line, t_envvar **envp);

void	ft_prompt_execution(t_token *token_list, t_envvar **envp);

/* ************************************************************************** */

/* SETUP ******************************************************************** */

char	*ft_dq_holder(char *addr, int type);

char	*ft_hd_holder(char *addr, int type);

t_node	*ft_tree_holder(int reset, t_node *root);

void	ft_signal_state(int toggle);
/* ************************************************************************** */

void	ft_display_token(t_token *token);

void	start_execve(t_command *cmd, t_executor *ex);

void	ft_error_message(t_error_code err, char *str);

#endif