/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:16:19 by marvin            #+#    #+#             */
/*   Updated: 2024/01/16 16:16:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "libft.h"

# include "data_structures.h"
# include "builtins.h"
# include "parser.h"

# define P_SUCCESS "\001\033[30;102;1m\002$?\001\033[0m\002 "
# define P_FAIL "\001\033[30;101;1m\002$?\001\033[0m\002 "
# define P_TAIL "\001\033[30;47;3;1m\002[Minishell]:\001\033[0m\002 "

# define P_SDQUOTE "\001\033[30;106;1m\002''\001\033[0m\002 "
# define P_DDQUOTE "\001\033[30;104;1m\002\"\"\001\033[0m\002 "
# define P_ENDQUOTE "\001\033[30;47;3;1m\002   [dquote]:\001\033[0m\002 > "

/**
 * @brief				Exit Handler. 
 * (A LAVENIR CETTE MERDE DOIT FREE TOUT LE CODE JAI DEJA UNE IDEE ON VERRA PLUS TARD OUBLIE PAS LES STATIC ET LES DETOURNEMENTS DE NORME)
 * 
 * @param exit_code		Exit code.
 * @param ec			Error code (see enum e_error_code).
 * @param cmd			t_command pointer with command meta-data.
 * @param prompt		Prompt line pointer.
*/
void	ft_exit_manager(int exit_code, int ec, t_command *cmd, char *prompt);


/* ************************************************************************** */
char	*ft_get_pwd(void);


/* PARSING ****************************************************************** */
char	*parse_quotes(char *string);
char	*parse_dollar(char *string, t_envvar *envp);
int		ft_qs_update(char c, t_quote_state *qs);
char	*str_add(char *dest, char *src, size_t place);
char	*str_append(char *str, char c);
char	*str_add(char *dest, char *src, size_t place);
/* ************************************************************************** */

/* PROMPTING **************************************************************** */
void	ft_prompt(t_envvar *envp);

/**
 * @brief				Get prompt total string.
 * 
 * @param envp			Linked list.
 * 
 * @return				Formatted total prompt string.
*/
char	*ft_get_prompt_string(t_envvar *envp);

char	*ft_quote_checker(char *str, t_quote_state oldqs);
char	*ft_open_dquote(t_quote_state qs);
/* ************************************************************************** */

/* SETUP ******************************************************************** */



void		toggle_signal(int toggle);
/* ************************************************************************** */

#endif