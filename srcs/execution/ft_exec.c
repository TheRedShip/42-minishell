/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/20 21:23:08 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;
extern int	DEBUG;

void	ft_exec(t_node *tree, t_executor *ex, t_exec_status status)
{
	// printf("DEBUG: execution of %p node\n", tree);
	if (DEBUG)
		ft_display_node(tree);
	if (tree->token && tree->token->type & TK_BINOPS)
	{
		if (!ft_strncmp(tree->token->str, "&&", 2))
			ft_exec_and(tree, ex, status);
		if (!ft_strncmp(tree->token->str, "||", 2))
			ft_exec_or(tree, ex, status);
	}
	if (tree->command && tree->command->path)
		ft_exec_command(tree, ex, status);
	if (tree == ex->root)
	{
		ft_close_executor(ex);
		ft_del_executor(ex);
	}
}

int	ft_process_redirs(t_command *cmd, t_executor *ex)
{
	int	in_file;
	int out_file;
	
	in_file = STDIN_FILENO;
	out_file = STDOUT_FILENO;
	if (ex->pipes)
	{
		in_file = ex->input;
		out_file = ex->output;
	}
	if (cmd->infile != STDIN_FILENO)
		in_file = cmd->infile;
	if (cmd->outfile != STDOUT_FILENO)
		out_file = cmd->outfile;
	dup2(in_file, STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
	return (ERR_NOERRS);
}

void	ft_process_bredirs(t_command *cmd, t_executor *ex, int **tmps)
{
	int	in_file;
	int	out_file;

	in_file = STDIN_FILENO;
	out_file = STDOUT_FILENO;
	(*tmps)[STDIN_FILENO] = dup(STDIN_FILENO);
	(*tmps)[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (ex->pipes)
	{
		in_file = ex->input;
		out_file = ex->output;
	}
	if (cmd->infile != STDIN_FILENO)
		in_file = cmd->infile;
	if (cmd->outfile != STDOUT_FILENO)
		out_file = cmd->outfile;
	dup2(in_file, STDIN_FILENO);
	dup2(out_file, STDOUT_FILENO);
}

void	ft_exec_or(t_node *tree, t_executor *ex, t_exec_status status)
{
	if (DEBUG)
		printf("%p OR %p\n", tree->left, tree->right);
	ft_exec(tree->left, ex, EX_WAIT);
	if (g_exit_code != ERR_NOERRS)
		ft_exec(tree->right, ex, status);
}

void	ft_exec_and(t_node *tree, t_executor *ex, t_exec_status status)
{
	if (DEBUG)
		printf("%p AND %p\n", tree->left, tree->right);
	ft_exec(tree->left, ex, EX_WAIT);
	if (g_exit_code == ERR_NOERRS)
		ft_exec(tree->right, ex, status);
}

void	ft_exec_command(t_node *tree, t_executor *ex, t_exec_status status)
{
	int	*btemps;
	int	built;

	(void) status;
	if (ft_open_inputs(tree))
	{
		ft_close_command(tree->command);
		g_exit_code = 1;
		return ;
	}
	btemps = ft_calloc(2, sizeof(int));
	ft_command_checker(tree->command);
	built = ft_exec_builtins(tree->command, ex, &btemps);
	if (built)
		start_execve(tree->command, ex);
	else
	{
		dup2(btemps[0], STDIN_FILENO);
		dup2(btemps[1], STDOUT_FILENO);
		close(btemps[0]);
		close(btemps[1]);
	}
	free(btemps);
	ft_close_command(tree->command);
}

int	ft_exec_builtins(t_command	*cmd, t_executor *ex, int **btemps)
{
	char		*trim;
	char		**tmp;
	static int	(*builtins[7])(t_command *) = \
	{&ft_cd, &ft_pwd, &ft_echo, &ft_env, &ft_export, &ft_unset, &ft_exit};
	static char	*builtins_str[8] = \
	{"cd", "pwd", "echo", "env", "export", "unset", "exit", NULL};

	tmp = builtins_str;
	trim = ft_strrchr(cmd->path, '/');
	if (!trim || !(trim + 1))
		return (ERR_FAILED);
	trim++;
	while (*tmp && ft_strncmp(trim, *tmp, ft_strlen(*tmp) + 1))
	{
		trim = ft_strrchr(cmd->path, '/') + 1;
		tmp++;
	}
	if (!*tmp)
		return (ERR_FAILED);
	else
	{
		ft_process_bredirs(cmd, ex, btemps);
		g_exit_code = builtins[tmp - builtins_str](cmd);
	}
	return (ERR_NOERRS);
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
// 		ft_format_tokens(&token_list, ft_get_var(environment, "HOME"));
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
// 		ft_exec(tree, ex);

// 		ft_clear_token_list(token_list);
// 		ft_clear_tree(tree);
// 		free(command);
// 		command = readline("");
// 		printf("\033c");
// 	}
// 	ft_clear_env(environment);
// }
