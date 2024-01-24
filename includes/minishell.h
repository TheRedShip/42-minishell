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
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "libft.h"

# include "data_structures.h"

# define P_SUCCESS "\033[30;42;1m$?\033[0m \033[30;47;1;3m[MINISHELL]:\033[0m "
# define P_FAIL "\033[30;41;1m$?\033[0m \033[30;47;1;3m[MINISHELL]:\033[0m "

# define P_SDQUOTE "\033[30;44;1m>>\033[0m \033[30;47;1;3m[' dquote]:\033[0m > "
# define P_DDQUOTE "\033[30;44;1m>>\033[0m \033[30;47;1;3m[\" dquote]:\033[0m > "

/* BUILT-INS **************************************************************** */
int		ft_exit(char *line);
int		ft_echo(char **args);
int		ft_pwd(void);
int 	ft_cd(char **args, t_envvar *envp);
void	ft_export(t_command *cmd, t_envvar env);
/* ************************************************************************** */
char	*ft_get_pwd(void);


/* PARSING ****************************************************************** */
char	*parse_quotes(char *string);
char	*str_add(char *dest, char *src, size_t place);
/* ************************************************************************** */

/* PROMPTING **************************************************************** */
void	ft_prompt(t_envvar *envp, char **envpstring);
char	*ft_get_prompt_string(t_envvar *envp);
/* ************************************************************************** */

/* SETUP ******************************************************************** */
t_envvar    *ft_setup_env(char **envp);
void		toggle_signal(int toggle);
/* ************************************************************************** */

#endif