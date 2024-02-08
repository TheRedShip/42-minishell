/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:07:11 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/08 22:14:41 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envvar    *ft_init_var(char *value)
{
	t_envvar    *new_var;
	char		*equal;
	char        *name;
	char		**tmp;

	(void) name;
	new_var = malloc(sizeof(t_envvar));
	if (!new_var)
		return (NULL);
	equal = ft_strchr(value, '=');
	if (equal)
	{
		tmp = ft_split(value, '=');
		new_var->name = ft_strdup(tmp[0]);
		ft_free_tab((void **)tmp);
		new_var->values = ft_split(equal + 1, ':');
	}
	else
	{
		new_var->name = ft_strdup(value);
		new_var->values = NULL;
	}
	new_var->next = NULL;
	return (new_var);
}

t_command	*ft_init_command(int input, int output, char *raw_cmd, t_envvar **envp)
{
	t_command	*new_command;
	char		**args;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->infile = input;
	new_command->outfile = output;
	new_command->path = NULL;
	args = ft_split(raw_cmd, ' ');
	if (args && args[0])
		new_command->path = ft_get_path(args[0], *envp);
	new_command->args = args;
	new_command->envp = envp;
	return (new_command);
}

t_node	*ft_init_node(t_command *command, t_token *token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->command = command;
	new_node->token = token;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_token	*ft_init_token(char *str, t_token_type type)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = str;
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}
