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

// COMMANDS

int		ft_exit(char *line);
int		ft_echo(char **args);
int		ft_pwd(void);
int 	ft_cd(char **args);

// PARSING

char	*parse_quotes(char *string);
char	*str_add(char *dest, char *src, size_t place);

// PROMPT

void	ft_prompt(char **envp);
#endif