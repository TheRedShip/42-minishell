/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:47:41 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/11 23:15:58 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_cmd_token(t_token **tokens, t_envvar **env)
{
	t_node		*cmd_node;
	t_token		*tmp;
	char		**args;
	int			fds[3];

	args = NULL;
	tmp = *tokens;
	ft_memset(fds, 0, 3 * sizeof(int));
	fds[1] = 1;
	while (tmp && (tmp->type & (TK_STRING | TK_REDIRS)))
	{
		if (tmp->type & TK_REDIRS)
		{
			ft_manage_inputs(&tmp, &(fds[0]), &(fds[2]));
			ft_manage_outputs(&tmp, &(fds[1]));
		}
		else if (tmp->type & TK_STRING)
			ft_strapp(&args, ft_strdup(tmp->str));
		tmp = tmp->next;
	}
	cmd_node = ft_init_node(ft_init_command(fds[0], fds[1], args, env), NULL);
	*tokens = tmp;
	return (cmd_node);
}

void	treeprint(t_node *root, int space)
{
	if (root == NULL)
		return ;
	space += 8;
	treeprint(root->right, space);
	printf("\n");
	for (int i = 8; i < space; i++)
	{
		printf(" ");
	}
	if (root->command)
	{
		printf(" %s ", root->command->path);
		printf("[%d] -> [%d]\n", root->command->infile, root->command->outfile);
	}
	if (root->token)
		printf("[%s]\n", root->token->str);
	treeprint(root->left, space);
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
	t_token	*tmp;

	tmp = ft_dup_token(*tk);
	if ((*tk)->type & TK_BINOPS)
		ft_associate(tree, ft_build_tree((*tk)->next, env), NULL, tmp);
	else if ((*tk)->type & TK_PIPEXS)
	{
		ft_insert_parent(tree, ft_init_node(NULL, tmp), LEFT);
		(*tk) = (*tk)->next;
	}
}

t_node	*ft_build_tree(t_token *tokens, t_envvar **env)
{
	t_node			*tree;
	t_token_type	tmp;

	tree = NULL;
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
			ft_insert_child(&tree, ft_cmd_token(&tokens, env), RIGHT);
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

// int	max_depth(t_node *tree)
// {
// 	int	max;

// 	max = 0;
// 	if (!tree)
// 		return (max);
// 	return (1 + ft_max(max_depth(tree->left), max_depth(tree->right)));
// }

// int main(int argc, char **argv, char **envp)
// {
// 	(void) argc;

// 	// char *str = ft_strdup("echo bonjour && (echo bonjour | (rev || cat && rev | (rev|cat)))");
// 	char *str = ft_strdup("(echo a | rev) || (echo a | (cat && rev)) | (echo a | rev) || (echo a | (cat && rev)) && echo bonjour && (echo bonjour | (rev || cat && rev | (rev|cat)))");
// 	// char *str = ft_strdup("echo abcd | rev && echo bef");
// 	// char *str = ft_strdup("echo bonjour | rev && rev | cat | cat | cat");


// 	t_token *tokens = ft_tokenizer(str, QU_ZERO);
// 	ft_format_tokens(&tokens);
// 	ft_remove_braces(&tokens);

// 	t_token *t;

// 	t = tokens;
// 	printf("------------- ACTUAL TOKEN LIST -------------\n");
// 	while (t)
// 	{
// 		printf("%s ", t->str);
// 		t = t->next;
// 	}
// 	printf("\n---------------------------------------------\n");


// 	if (tokens && !ft_verify_token(tokens))
// 	{
// 		ft_putstr_fd("minishell: syntax error\n", 1);
// 		exit(EC_FAILED);
// 	}

// 	// t_token *t;

// 	// t = tokens;
// 	// printf("------------- ACTUAL TOKEN LIST -------------\n");
// 	// while (t)
// 	// {
// 	// 	ft_display_token(t);
// 	// 	t = t->next;
// 	// }
// 	// printf("\n---------------------------------------------\n");

// 	t_envvar *env = ft_setup_env(argv, envp);
// 	t_node *tree = ft_build_tree(tokens, &env);
// 	treeprint(tree, 0);
// 	// ft_display_node(tree);

// 	ft_clear_token_list(tokens);
// 	ft_clear_tree(tree);
// 	ft_clear_env(env);
// 	free(str);
// }
