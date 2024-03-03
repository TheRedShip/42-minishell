/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:47:41 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 19:26:32 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_cmd_token(t_token **tokens, t_envvar **env, t_token *tmp)
{
	char	**args;
	t_redir	*redirs;

	args = NULL;
	redirs = NULL;
	while (tmp && (tmp->type & (TK_STRING | TK_REDIRS)))
	{
		if (tmp->type & TK_REDIRS)
		{
			ft_add_redir(&redirs, ft_init_redir(tmp));
			tmp = tmp->next;
		}
		else if (tmp->type & TK_STRING)
			ft_strapp(&args, ft_strdup(tmp->str));
		tmp = tmp->next;
	}
	*tokens = tmp;
	return (ft_init_node(ft_init_command(redirs, args, env), NULL));
}

void	ft_brace_tree(t_token **tk, t_node **tree, t_envvar **env)
{
	t_node		*test;
	int			level;

	test = ft_build_tree((*tk)->next, env);
	level = 0;
	if (!tree)
		*tree = test;
	else
		ft_insert_child(tree, test, RIGHT);
	(*tk) = (*tk)->next;
	while ((*tk) && (!((*tk)->type & TK_BRACES && \
			!ft_strncmp((*tk)->str, ")", 2)) || level))
	{
		if ((*tk)->type & TK_BRACES && !ft_strncmp((*tk)->str, "(", 2))
			level++;
		if ((*tk)->type & TK_BRACES && !ft_strncmp((*tk)->str, ")", 2))
			level--;
		(*tk) = (*tk)->next;
	}
	(*tk) = (*tk)->next;
}

void	ft_connect_ops(t_token **tk, t_node **tree, t_envvar **env)
{
	t_node	*next;

	next = NULL;
	if ((*tk)->type & TK_BINOPS)
	{
		next = ft_build_tree((*tk)->next, env);
		ft_associate(tree, next, NULL, ft_dup_token(*tk));
	}
	else if ((*tk)->type & TK_PIPEXS)
	{
		ft_insert_parent(tree, ft_init_node(NULL, ft_dup_token(*tk)), LEFT);
		(*tk) = (*tk)->next;
	}
}

t_node	*ft_build_tree(t_token *tokens, t_envvar **env)
{
	t_node			*tree;
	t_token_type	tmp;

	tree = NULL;
	ft_update_env(env);
	while (tokens)
	{
		if (tokens->type & TK_BRACES)
		{
			if (!ft_strncmp(tokens->str, "(", 2))
				ft_brace_tree(&tokens, &tree, env);
			else
				return (tree);
		}
		else if (tokens->type & (TK_STRING | TK_REDIRS))
			ft_insert_child(&tree, ft_cmd_token(&tokens, env, tokens), RIGHT);
		if (!tokens)
			return (tree);
		tmp = tokens->type;
		if (tmp & (TK_BINOPS | TK_PIPEXS))
			ft_connect_ops(&tokens, &tree, env);
		if (tmp & TK_BINOPS)
			return (tree);
	}
	return (tree);
}
