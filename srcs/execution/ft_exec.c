/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/26 12:18:39 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

// void	ft_exec(t_node *tree, t_executor *ex, t_exec_status status)
// {
// 	if (tree->token && tree->token->type & TK_BINOPS)
// 	{
// 		if (!ft_strncmp(tree->token->str, "&&", 2))
// 			ft_exec_and(tree, ex, status);
// 		if (!ft_strncmp(tree->token->str, "||", 2))
// 			ft_exec_or(tree, ex, status);
// 	}
// 	if (tree->token && tree->token->type & TK_PIPEXS)
// 		ft_exec_pipe(tree, ex, status);
// 	if (tree->command)
// 		ft_exec_command(tree, ex, status);
// 	if (tree == ex->root)
// 	{
// 		ft_close_executor(ex);
// 		ft_del_executor(ex);
// 	}
// }

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
	if (in_file != STDIN_FILENO)
		dup2(in_file, STDIN_FILENO);
	if (out_file != STDOUT_FILENO)
		dup2(out_file, STDOUT_FILENO);
	return (ERR_NOERRS);
}

void	ft_process_bredirs(t_command *cmd, t_executor *ex, int *tmps)
{
	int	in_file;
	int	out_file;

	in_file = STDIN_FILENO;
	out_file = STDOUT_FILENO;
	tmps[0] = dup(STDIN_FILENO);
	tmps[1] = dup(STDOUT_FILENO);
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

// void	ft_exec_pipe(t_node *tree, t_executor *ex, t_exec_status status)
// {
// 	if (status == EX_WAIT)
// 		ft_pipes_push(&(ex->pipes), ft_init_pipes());
// 	ft_exec(tree->left, ex, EX_PIPE);
// 	ft_exec(tree->right, ex, EX_PIPE);
// 	ft_pipeline_exit(ex);
// }

// void	ft_exec_or(t_node *tree, t_executor *ex, t_exec_status status)
// {
// 	ft_exec(tree->left, ex, EX_WAIT);
// 	if (g_exit_code != ERR_NOERRS)
// 		ft_exec(tree->right, ex, status);
// }

// void	ft_exec_and(t_node *tree, t_executor *ex, t_exec_status status)
// {
// 	ft_exec(tree->left, ex, EX_WAIT);
// 	if (g_exit_code == ERR_NOERRS)
// 		ft_exec(tree->right, ex, status);
// }

void	ft_command_exit(t_command *cmd, t_executor *ex)
{
	int err_code;

	if (!ex->pipes)
		waitpid(ex->base, &err_code, 0);
	else
		waitpid(ex->pipes->waitlist->pid, &err_code, 0);
	g_exit_code = WEXITSTATUS(err_code);
	if (!WIFEXITED(err_code) && WCOREDUMP(err_code))
	{
		printf("Quit (core dumped)\n");
		g_exit_code = 131;
	}
	else if (WTERMSIG(err_code) == 2)
	{
		ft_printf("\n");
		g_exit_code = 130;
	}
	if (ft_strnstr(cmd->path, "clear", ft_strlen(cmd->path)) && !g_exit_code)
		ft_print_logo(*(cmd->envp));
}

// void	ft_pipeline_exit(t_executor *ex)
// {
// 	t_pid	*curr;
// 	int		err_code;

// 	curr = NULL;
// 	while (ex->pipes->waitlist)
// 	{
// 		curr = ft_pid_pop(&(ex->pipes->waitlist));
// 		waitpid(curr->pid, &err_code, 0);
// 		free(curr);
// 	}
// 	g_exit_code = WEXITSTATUS(err_code);
// 	if (!WIFEXITED(err_code) && WCOREDUMP(err_code))
// 	{
// 		printf("Quit (core dumped)\n");
// 		g_exit_code = 131;
// 	}
// 	else if (WTERMSIG(err_code) == 2)
// 	{
// 		ft_printf("\n");
// 		g_exit_code = 130;
// 	}
// 	free(ft_pipes_pop(&(ex->pipes)));
// }

void	start_execve(t_command *cmd, t_executor *ex, t_exec_status status)
{
	char	**env;
	pid_t	pid;
	DIR		*file_check;

	ft_signal_state(SIGHANDLER_IGN);
	if (!ex->pipes)
	{
		ex->base = fork();
		pid = ex->base;
	}
	else
	{
		ft_pid_push(&(ex->pipes->waitlist), ft_init_pid(fork()));
		pid = ex->pipes->waitlist->pid;
	}
	if (pid == 0)
	{
		env = ft_get_var_strs(*(cmd->envp), 0);
		rl_clear_history();
		if (ft_process_redirs(cmd, ex) == ERR_ERRORS)
		{
			ft_free_tab((void **)env);
			ft_clear_env(*(cmd->envp));
			ft_clear_tree(ex->root);
			ft_del_executor(ex);
			exit(ERR_FAILED);
		}
		ft_close_executor(ex);
		file_check = opendir(cmd->path);
		if (errno != ENOTDIR)
		{
			ft_error_message(ERR_NOPERM, cmd->path);
			closedir(file_check);
			ft_free_tab((void **)env);
			ft_clear_env(*(cmd->envp));
			ft_clear_tree(ex->root);
			ft_del_executor(ex);
			exit(126);
		}
		closedir(file_check);
		execve(cmd->path, cmd->args, env);
		perror("execve");
		exit(ERR_FAILED);
	}
	else if (pid < 0)
		perror("fork");
	ft_signal_state(SIGHANDLER_INT);
	if (status == EX_WAIT)
		ft_command_exit(cmd, ex);
}

int	ft_cmd_start(t_node *tree, t_executor *ex, int *b_fds)
{
	int		flags;
	char	*err_str;

	flags = 0b0000;
	err_str = NULL;
	ft_command_checker(tree->command);
	flags |= (tree->command->path && !*tree->command->path);
	flags |= (ft_open_outputs(tree) || ft_open_inputs(tree)) << 1;
	flags |= (!tree->command->path || access(tree->command->path, F_OK)) << 2;
	g_exit_code = (flags & 0b0010);
	if (flags & 0b0011)
		return (ERR_FAILED);
	if (flags & 0b0100)
		g_exit_code = 127;
	flags |= ft_exec_builtins(tree->command, ex, b_fds) << 3;
	if ((flags & 0b0100) && (flags & 0b1000))
	{
		if (tree->command->args && *tree->command->args)
			err_str = *tree->command->args;
		ft_error_message(ERR_NOTCMD, err_str);
		return (ERR_FAILED);
	}
	if (flags & 0b1000)
		return (ERR_NOTCMD);
	return (ERR_NOERRS);
}

void	ft_exec_command(t_node *tree, t_executor *ex, t_exec_status status)
{
	int				b_fds[2];
	t_error_code	err_code;

	(void) status;
	b_fds[0] = STDIN_FILENO;
	b_fds[1] = STDOUT_FILENO;
	err_code = ft_cmd_start(tree, ex, (int *)b_fds);
	if (err_code == ERR_FAILED)
		return ;
	else if (err_code == ERR_NOTCMD)
		start_execve(tree->command, ex, status);
	else
	{
		dup2(b_fds[0], STDIN_FILENO);
		dup2(b_fds[1], STDOUT_FILENO);
		if (b_fds[0] > 2)
			close(b_fds[0]);
		if (b_fds[1] > 2)
			close(b_fds[1]);
	}
}

int	ft_exec_builtins(t_command	*cmd, t_executor *ex, int *b_fds)
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
		tmp++;
	if (!*tmp)
		return (ERR_FAILED);
	if (tmp - builtins_str != 6)
		ft_process_bredirs(cmd, ex, b_fds);
	g_exit_code = builtins[tmp - builtins_str](cmd);
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
