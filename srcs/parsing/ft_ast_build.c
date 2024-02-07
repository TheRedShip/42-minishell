/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:47:41 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/08 00:26:06 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_heredoc(char *str)
{
	(void) str;
	
	return (10);
}

int	ft_manage_file(t_token **tokens, int **fds)
{
	int		state;

	state = !ft_strncmp((*tokens)->str, "<", 2) + 2 * !ft_strncmp((*tokens)->str, "<<", 3);
	printf("TESTING: state = [%d]\n", state);
	if (state)
	{
		printf("DEBUG :  OPENING INFILE: current = [%d], state = [%d]\n", (*fds)[0], state);
		if ((*fds)[0] > 2)
		{
			// printf("I CLOSE [%d]\n", (*fds)[0]);
			close((*fds)[0]);
		}
		if (state & 0b01)
			(*fds)[0] = open(((*tokens)->next)->str, OPEN_READ);
		else if (state & 0b10 && (*fds)[2] < 16)
		{
			(*fds)[0] = ft_get_heredoc(((*tokens)->next)->str);
			(*fds)[2]++;
		}
		else
			return (EC_FAILED);
		printf("FILE OPENED: fd = [%d]\n", (*fds)[0]);
	}
	state = !ft_strncmp((*tokens)->str, ">", 2) + 2 * !ft_strncmp((*tokens)->str, ">>", 3);
	// printf("TESTING: state = [%d]\n", state);
	if (state)
	{
		printf("DEBUG : OPENING OUTFILE: current = [%d], state = [%d]\n", (*fds)[1], state);
		if ((*fds)[1] > 2)
		{
			// printf("I CLOSE [%d]\n", (*fds)[1]);
			close((*fds)[1]);
		}
		if (state & 0b01)
			(*fds)[1] = open(((*tokens)->next)->str, OPEN_CREATE, 0644);
		else if (state & 0b10)
			(*fds)[1] = open(((*tokens)->next)->str, OPEN_APPEND, 0644);
		printf("FILE OPENED: fd = [%d]\n", (*fds)[1]);
	}
	(*tokens) = (*tokens)->next;
	return (EC_SUCCES);
}

t_node	*ft_convert_tokens(t_token **tokens, int braced, t_envvar **env)
{
	t_node		*cmd_node;
	t_token		*tmp;
	int			*fds;	// fds[0] = input file, fds[1] = output file, fds[2] = hd count
	char		*raw;

	raw = NULL;
	tmp = *tokens;
	fds = malloc(3 * sizeof(int));
	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 0;
	while (tmp && (tmp->type & (TK_STRING | TK_REDIRS)))
	{
		if (tmp->type & TK_REDIRS)
			ft_manage_file(&tmp, &fds);
		else if (tmp->type & TK_STRING)
			raw = ft_strjoin(raw, tmp->str, " ", 0b01);
		tmp = tmp->next;
	}
	cmd_node = ft_init_node(braced, \
				ft_init_command(fds[0], fds[1], raw, env), NULL);
	free(raw);
	free(fds);
	*tokens = tmp;
	return (cmd_node);
}

void treeprint(t_node *root, int space)
{
    if (root == NULL)
        return;
    space += 10;
    treeprint(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
	{
        printf(" ");
	}
	if (root->command)
    	printf("%s\n", root->command->path);
	if (root->token)
		printf("%s\n", root->token->str);
    treeprint(root->left, space);
}

t_node	*ft_build_tree(t_token *tokens, int braced, t_envvar **env)
{
	t_node		*tree;
	t_token		*tmp;

	(void) env;
	tree = NULL;
	while (tokens)
	{
		// if (tokens->type & TK_BRACES)
		// {
		// 	if (!ft_strncmp(tokens->str, "(", 2))
		// 	{
		// 		t_node *test = ft_build_tree(tokens->next, 1, env);
		// 		if (!tree)
		// 			tree = test;
		// 		else
		// 			ft_insert_child(&tree, test, RIGHT);
		// 		tokens = tokens->next;
		// 		while (tokens && !(tokens->type & TK_BRACES) && ft_strncmp(tokens->str, ")", 2))
		// 			tokens = tokens->next;
		// 		tokens = tokens->next;
		// 	}
		// 	else
		// 		return (tree);
		// }
		if (tokens->type & (TK_STRING | TK_REDIRS))
			ft_insert_child(&tree, ft_convert_tokens(&tokens, braced, env), RIGHT);
		if (!tokens)
			return (tree);
		if (tokens->type & (TK_BINOPS | TK_PIPEXS))
		{
			tmp = ft_dup_token(tokens);
			ft_insert_parent(&tree, ft_init_node(braced, NULL, tmp), LEFT);
			tokens = tokens->next;
		}
	}
	return (tree);
}

// void treeprint(t_node *root, int level)
// {
// 	if (root == NULL)
// 		return ;
// 	for (int i = 0; i < level; i++)
// 		printf(i == level - 1 ? "└" : " ");
// 	if (root->token)
//     	printf("TOKEN : [%s]\n\n", root->token->str);
// 	if (root->command)
// 		printf("COMMAND [%s]\n\n", root->command->path);
// 	treeprint(root->left, level + 1);
// 	treeprint(root->right, level + 1);
// }


// int main(int argc, char **argv, char **envp)
// {
// 	(void) argc;

// 	char *str = ft_strdup("cat -P || cat Makefile | rev");
// 	t_token *tokens = ft_tokenizer(str, QU_ZERO);

// 	t_token *t;

// 	t = tokens;
// 	printf("------------- ACTUAL TOKEN LIST -------------\n");
// 	while (t)
// 	{
// 		ft_display_token(t);
// 		t = t->next;
// 	}
// 	printf("\n---------------------------------------------\n");

// 	t_envvar *env = ft_setup_env(argv, envp);
// 	t_node *tree = ft_build_tree(tokens, 0, &env);
// 	treeprint(tree, 0);
// }

/*
	(
		{salut}
				||
		{toi}
	)
					&&

*/
