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

/* BUILT-INS **************************************************************** */
int		ft_exit(char *line);
int		ft_echo(char **args);
int		ft_pwd(void);
int 	ft_cd(char **args);
void	ft_export(t_command *cmd, t_envvar env);
/* ************************************************************************** */

/* PARSING ****************************************************************** */
char	*parse_quotes(char *string);
char	*str_add(char *dest, char *src, size_t place);
/* ************************************************************************** */

/* STRUCT ******************************************************************* */
void	ft_prompt(t_envvar *envp, char **envpstring);
/* ************************************************************************** */

/* SETUP ******************************************************************** */
t_envvar    *ft_setup_env(char **envp);
void		toggle_signal(int toggle);
/* ************************************************************************** */

#endif