/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/15 20:10:32 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_exec(t_node *tree, t_executor *ex)
{
	printf("DEBUG: execution of %p node\n", tree);
	// ft_display_node(tree);
	if (tree->token && tree->token->type & TK_BINOPS)
	{
		if (!ft_strncmp(tree->token->str, "&&", 2))
			ft_exec_and(tree, ex);
		if (!ft_strncmp(tree->token->str, "||", 2))
			ft_exec_or(tree, ex);
	}
	if (tree->command)
		ft_exec_command(tree, ex);
}

void	ft_process_redirs(t_command *cmd, t_executor *ex)
{
	if (!ex->pipes)
	{
		if (cmd->infile != STDIN_FILENO)
			dup2(cmd->infile, STDIN_FILENO);
		if (cmd->outfile != STDOUT_FILENO)
			dup2(cmd->outfile, STDOUT_FILENO);
	}
	else
	{ //PAS VRAINMET LE BON CODE MAIS ON TEST PAS CA POUR LINSTANT NIQUE SA MERE
		dup2(ex->input, STDIN_FILENO);
		dup2(ex->output, STDOUT_FILENO);
	}
	ft_close_executor(ex);
}

void	ft_exec_or(t_node *tree, t_executor *ex)
{
	printf("%p OR %p\n", tree->left, tree->right);
	ft_exec(tree->left, ex);
	if (g_exit_code != EC_SUCCES)
		ft_exec(tree->right, ex);
}

void	ft_exec_and(t_node *tree, t_executor *ex)
{
	printf("%p AND %p\n", tree->left, tree->right);
	ft_exec(tree->left, ex);
	if (g_exit_code == EC_SUCCES)
		ft_exec(tree->right, ex);
}

void	ft_exec_command(t_node *tree, t_executor *ex)
{
	// int		pid;
	// char	**env;

	(void) ex;
	start_execve(tree->command);
	// env = ft_get_var_strs(*(tree->command->envp), 0);
	// pid = fork();
	// if (!pid)
	// {
	// 	ft_process_redirs(root, tree->command, ex);
	// 	execve(tree->command->path, tree->command->args, env);
	// }
	// waitpid(pid, &status);
	// g_exit_code = WEXITSTATUS(status);
	ft_close_command(tree);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*command = NULL;
// 	t_envvar	*environment = ft_setup_env(argv, envp);
// 	t_token		*token_list;
// 	int			fd_command;;
// 	char		**test_commands = NULL;
// 	char		*line;

// 	(void) argc;
// 	fd_command = open("commands.tst", O_RDONLY);
// 	printf("%d\n", fd_command);
// 	while ((line = get_next_line(fd_command)))
// 		ft_strapp(&test_commands, ft_strtrim(line, "\n"));
// 	close(fd_command);
// 	free(command);

// 	while (1)
// 	{
// 		command = readline("num ?: ");
// 		if (!command)
// 			continue ;
// 		if (!ft_strncmp("exit", command, 4))
// 			exit(EXIT_SUCCESS);
// 		char *tmp = command;
// 		while (*tmp && ft_isdigit(*tmp))
// 			tmp++;
// 		if (*tmp || !*command)
// 			continue ;
// 		int cmd_num = ft_atoi_base(command, 10);
// 		free(command);
// 		if (cmd_num < 0 || cmd_num > ft_tab_len(test_commands))
// 			continue ;
// 		if (!cmd_num)
// 			continue ;
// 		command = ft_strdup(*(test_commands + cmd_num - 1));
// 		token_list = ft_tokenizer(command, QU_ZERO);
// 		ft_format_tokens(&token_list);
// 		ft_remove_braces(&token_list);
// 		t_token *t;
// 		t = token_list;
// 		printf("------------- ACTUAL TOKEN LIST -------------\n");
// 		while (t)
// 		{
// 			printf("%s ", t->str);
// 			t = t->next;
// 		}
// 		printf("\n---------------------------------------------\n");
// 		t_node *tree = ft_build_tree(token_list, &environment);
// 		treeprint(tree, 0);
// 		printf("\n");

// 		if (!tree || (!tree->token && !tree->command))
// 			continue ;

// 		t_executor *ex = malloc(sizeof(t_executor));
// 		ex->input = 0;
// 		ex->output = 1;
// 		ex->pipes = NULL;
// 		ex->pids = NULL;
// 		ft_exec(tree, tree, ex);

// 		ft_clear_token_list(token_list);
// 		ft_clear_tree(tree);
// 		free(command);
// 		command = readline("");
// 		printf("\033c");
// 	}
// 	ft_clear_env(environment);
// }
