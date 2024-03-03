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

/* ************************************************************************** */
char	*ft_get_pwd(void);

int		ft_isnt_empty(char *str);

/* PARSING ****************************************************************** */
int		ft_qs_update(char c, t_qstate *qs);

int		ft_quote_handler(char **line, t_envvar **envp, int status);
/* ************************************************************************** */

/* PROMPTING **************************************************************** */
t_error	ft_prompt_line(t_envvar **envp, char **line);

t_error	ft_to_tokens(t_token **tokens, char *line, t_envvar **envp);

t_error	ft_to_tree(t_token **tokens, t_node **tree, t_envvar **envp);

void	ft_prompt_handler(t_envvar **envp);

/* ************************************************************************** */

/* SETUP ******************************************************************** */

char	*ft_dq_holder(char *addr, int type);

char	*ft_hd_holder(char *addr, int type);

t_node	*ft_tree_holder(int reset, t_node *root);

void	ft_signal_state(int toggle);

/* ************************************************************************** */

void	ft_display_token(t_token *token);

void	ft_error_message(t_error err, char *str);

#endif