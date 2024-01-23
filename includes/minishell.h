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


typedef enum e_token_type
{
	TK_BRACE = 1,
	TK_BINOP,
	TK_PIPES,
	TK_REDIR,
	TK_UNKNO
}   t_token_type;

typedef enum e_quote_state
{
	QU_ZERO = 0,
	QU_SINGLE,
	QU_DOUBLE
}	t_quote_state;

typedef struct s_token
{
	char            *value;
	t_token_type    type;
}   t_token;

typedef struct s_node
{
	int					rank;
	void				*element;
	struct s_token_node *left;
	struct s_token_node *right;
}	t_token_node;

typedef struct s_command
{
	int				infile;
	int				outfile;
	char			*path;
	char			**args;
	char			**envp;
}   t_command;

typedef struct s_envvar
{
	char			*name;
	char			**values;
	struct s_envvar	*next;
}	t_envvar;


/* THE ONE AND ONLY ********************************************************* */
int EXIT_CODE = 0;

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