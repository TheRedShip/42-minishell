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
# include "libft.h"

typedef enum e_token_type
{
	TK_BRACE = 1,
	TK_BINOP,
	TK_PIPES,
	TK_REDIR,
	TK_FILES,
	TK_CMMDS
}   t_token_type;

typedef struct s_token
{
	char            *value;
	t_token_type    type;
	struct s_token  *next;
}   t_token;

typedef struct s_command
{
	int				infile;
	int				outfile;
	char			*path;
	char			**args;
	char			**envp;
	struct s_cmd	*next;
}   t_command;

typedef struct s_envvar
{
	char			*name;
	char			**values;
	struct s_envvar	*next;
}	t_envvar;

/* BUILT-INS **************************************************************** */
int		ft_exit(char *line);
int		ft_echo(char **args);
int		ft_pwd(void);
int 	ft_cd(char **args);
/* ************************************************************************** */

/* PARSING ****************************************************************** */
char	*parse_quotes(char *string);
char	*str_add(char *dest, char *src, size_t place);
/* ************************************************************************** */

/* STRUCT ******************************************************************* */
void	ft_prompt(char **envp);
/* ************************************************************************** */

#endif