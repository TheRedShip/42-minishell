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

/* INCLUDES ***************************************************************** */

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

# include <sys/stat.h>

# include <termios.h>

# include <dirent.h>

# include "libft.h"

# include "ft_enumerates.h"

# include "ft_data_structures.h"

# include "ft_parsing.h"

# include "ft_builtins.h"

# include "ft_file_manager.h"

# include "ft_execution.h"

/* PROMPTS ****************************************************************** */

# define P_SUCCESS "\001\033[32;1m\002$?\001\033[0m\002 "

# define P_FAIL "\001\033[31;1m\002$?\001\033[0m\002 "

# define P_TAIL "\001\033[37;1m\002 Minishell$\001\033[0m\002 "

# define P_SDQUOTE "\001\033[36;1m\002''  dquote:\001\033[0m\002 > "

# define P_DDQUOTE "\001\033[34;1m\002\"\"  dquote:\001\033[0m\002 > "

# define P_HEREDOC "\001\033[35;1m\002HD  here-doc:\001\033[0m\002 > "

# define P_ERROR "\001\033[31;1m\002/!\\ ERROR! > "

# define P_WARNING "\001\033[33;1m\002/!\\ WARNING! > "

/* ERROR MESSAGES *********************************************************** */

# define ES_NOTSET "%scd: %s not set\n"

# define ES_NOFORD "%s%s no such file or directory\n"

# define ES_TMARGS "%s%s: too many arguments\n"

# define ES_NOTNUM "%s%s: numeric argument required\n"

# define ES_NOTVAL "%sexport: `%s': not a valid identifier\n"

# define ES_NOPERM "%s%s: Permission denied\n"

# define ES_ISADIR "%s%s: Is a directory\n"

# define ES_INVOPT "%s%s: Invalid option\n"

# define ES_HDSTOP "%s here-document delimited by end-of-file, (wanted `%s')\n"

# define ES_DQSTOP "%sunexpected EOF while looking for matching `%s\'\n"

# define ES_SYNTXQ "%ssyntax error%s\n"

# define ES_SYNTXT "%ssyntax error near unexcepted token `%s'\n"

# define ES_SYNTXL "%ssyntax error\n"

# define ES_HLIMIT "%smaximum here-document count exceeded\n"

# define ES_INVFDS "%s%s: no more fds. Aborting\n"

# define ES_AMBRED "%s%s: ambiguous redirect\n"

/* OPENING MODES ************************************************************ */

// O_RDONLY = 00
# ifndef OPEN_READ
#  define OPEN_READ 00
# endif

// O_WRONLY = 01 | O_CREAT = 0100 | O_TRUNC = 01000
# ifndef OPEN_CREATE
#  define OPEN_CREATE 01101
# endif

// O_WRONLY = 01 | O_CREAT = 0100 | O_APPEND = 02000
# ifndef OPEN_APPEND
#  define OPEN_APPEND 02101
# endif

// O_WRONLY = 01 | O_EXCL = 0200 | O_CREAT = 0100 | O_TRUNC = 01000
# ifndef OPEN_EXCL
#  define OPEN_EXCL 01301
# endif

/* PROMPTING **************************************************************** */

/**
 * @brief			Handle quote syntax.
 * 
 * @param line		Line adress to handle.	
*/
t_error		ft_quote_handler(char **line, t_envvar **envp, int status);

/**
 * @brief			Handle line typing, history and quote-related errors.
 * 
 * @param envp		Environment linked list adress.
 * @param line		Line allocation adress. (from ft_prompt_handler).
 * 
 * @return			ERR_FAILED, ERR_DQSTOP if an error occurs,
 * 					ERR_NOERRS otherwise.
*/
t_error		ft_prompt_line(char **line, t_envvar **envp);

/**
 * @brief			Handle line to tokens transformation.
 * 
 * @param tokens	Tokens linked list adress. (from ft_prompt_handler).
 * @param line		Line from line handler.
 * @param envp		Environment linked list adress.
 * 
 * @return			ERR_FAILED in case of error during tokenization,
 * 					ERR_NOERRS otherwise.
*/
t_error		ft_to_tokens(t_token **tokens, char *line, t_envvar **envp);

/**
 * @brief			Handle tokens to tree transformation and execution.
 * 
 * @param tokens	Tokens linked list adress. (from ft_prompt_handler).
 * @param tree		Tree adress (from ft_prompt_handler).
 * @param envp		Environment linked list adress.
 * 
 * @return			ERR_HDSTOP in case of Heredoc problem,
 * 					ERR_NOERRS otherwise.
*/
t_error		ft_to_tree_exec(t_token **tokens, t_node **tree, t_envvar **envp);

/**
 * @brief			Handle prompt loop.
 * 
 * @param envp		Environment linked list adress.
*/
void		ft_prompt_handler(t_envvar **envp);

/* CORE UTILS *************************************************************** */

/**
 * @brief			Adress holder for dquotes allocations needed to be freed
 * 					by a signal handler.
 * 
 * @param addr		Adress of the element to save.
 * @param type		Type of the element (0 for line_save, 1 for dquote fd).
 * 
 * @return			Last known adress of the asked element.
*/
char		*ft_dq_holder(char *addr, int type);

/**
 * @brief			Adress holder for heredoc allocations needed to be freed
 * 					by a signal handler.
 * 
 * @param addr`		Adress of the element to save.
 * @param type		Type of the element (0 for filename save, 1 for delim save,
 * 					2 for heredoc fd)
 * 
 * @return			Last known adress of the asked element.
*/
char		*ft_hd_holder(char *addr, int type);

/**
 * @brief			Adress holder for the tree root.
 * 
 * @param reset		Reset boolean. 1 to reset.
 * @param root		Tree root's pointer.
 * 
 * @return			Last known adress for the root node.
*/
t_node		*ft_tree_holder(int reset, t_node *root);

/**
 * @brief			Signal handler switch.
 * 
 * @param toggle	Signal handler to branch on main process. see enum.
*/
void		ft_signal_state(int toggle);

/**
 * @brief			Error handler
 * 
 * @param err		Error code linked to the error.
 * @param str		String part for the actual message.
*/
void		ft_error_message(t_error err, char *str);

/* ************************************************************************** */

#endif