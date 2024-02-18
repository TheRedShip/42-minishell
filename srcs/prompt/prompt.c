/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:16:41 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 18:16:41 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	start_execve(t_command *cmd, t_executor *ex)
{
	char	**env;
	pid_t	pid;
	int		status;

	if (!cmd->args)
		return ;
	if (!cmd->path || access(cmd->path, F_OK))
	{
		if (*cmd->args)
			printf("minishell: %s: command not found\n", *cmd->args);
		else
			printf("minishell: command not found\n");
		g_exit_code = 127;
		return ;
	}
	ft_signal_state(SIGHANDLER_IGN);
	env = ft_get_var_strs(*(cmd->envp), 0);
	pid = fork();
	if (pid == 0)
	{
		// ft_clear_env(*(cmd->envp));
		int test = 0;
		test = ft_process_redirs(cmd, ex);
		if (test == 2)
		{
			ft_free_tab((void **)env);
			ft_clear_env(*(cmd->envp));
			ft_clear_tree(ex->root);
			ft_del_executor(ex);
			exit(EC_FAILED);
		}
		ft_close_command(cmd);
		execve(cmd->path, cmd->args, env);
		perror("execve");
		exit(EC_FAILED);
	}
	else if (pid < 0)
		perror("fork");
	waitpid(pid, &status, 0);
	g_exit_code = WEXITSTATUS(status);
	if (!WIFEXITED(status) && WCOREDUMP(status))
	{
		printf("Quit (core dumped)\n");
		g_exit_code = 131;
	}
	else if (WTERMSIG(status) == 2)
	{
		printf("\n");
		g_exit_code = 130;
	}
	if (ft_strnstr(cmd->path, "clear", ft_strlen(cmd->path)) && !g_exit_code)
		ft_print_logo(*(cmd->envp));
	ft_free_tab((void **)(env));
	ft_signal_state(SIGHANDLER_INT);
}

int	ft_quote_handler(char **line, t_envvar **envp, int status)
{
	char	*dquote_file;
	char	*history_line;
	char	qs;

	if (!*line)
		return (EC_ERRORS);
	history_line = *line;
	dquote_file = ft_get_temp_file(".dquote", 16);
	if (ft_syntax_errors(*line, QU_ZERO))
	{
		status = ft_get_dquote(*line, envp, dquote_file);
		history_line = ft_get_dquote_line(*line, dquote_file, status);
	}
	add_history(history_line);
	free(dquote_file);
	*line = history_line;
	if (WEXITSTATUS(status) == 130)
	{
		free(*line);
		return (EC_FAILED);
	}
	qs = ft_syntax_errors(*line, QU_ZERO);
	if (qs)
		printf("%sunexpected EOF while looking for matching `%c\'\n", MINI, qs);
	return (EC_SUCCES);
}

void	ft_prompt_handle(t_envvar **envp)
{
	char	*line;
	char	*prompt;
	int		err_code;

	prompt = ft_get_prompt_string(*envp);
	line = readline(prompt);
	free(prompt);
	if (line && !ft_isnt_empty(line))
	{
		free(line);
		return ;
	}
	ft_signal_state(SIGHANDLER_IGN);
	err_code = ft_quote_handler(&line, envp, 0);
	ft_signal_state(SIGHANDLER_INT);
	if (err_code == EC_ERRORS)
		ft_clear_env(*envp);
	if (err_code == EC_ERRORS)
		ft_exit(NULL);
	else if (err_code == EC_FAILED || !line)
	{
		g_exit_code = 130;
		return ;
	}
	ft_prompt_tokenization(line, envp);
}

void	ft_display_token_list(t_token *token_list)
{
	/*
		DEBUG SECTION
	*/
	t_token *t;
	t = token_list;
	printf("------------- ACTUAL TOKEN LIST -------------\n");
	while (t)
	{
		printf("[%s]->", t->str);
		t = t->next;
	}
	printf("\n---------------------------------------------\n");
	/*
		END OF DEBUG
	*/
}

void	ft_prompt_tokenization(char *line, t_envvar **envp)
{
	t_token	*token_list;
	int		syntax;

	syntax = 0;
	token_list = ft_tokenizer(line, QU_ZERO);
	if (!token_list)
		return ;
	ft_format_tokens(&token_list, ft_get_var(*envp, "HOME"));
	ft_remove_braces(&token_list);
	ft_display_token_list(token_list);
	if ((!ft_verify_token(token_list) || ft_syntax_errors(line, QU_ZERO)))
	{
		printf("%ssyntax error\n", MINI);
		syntax++;
		g_exit_code = 2;
	}
	free(line);
	if (syntax)
	{
		ft_clear_token_list(token_list);
		return ;
	}
	ft_prompt_execution(token_list, envp);
}

void	ft_prompt_execution(t_token *token_list, t_envvar **envp) // REALLY LIGHT EXEC
{
	t_node		*tree;
	t_node		*first_command;
	int			check;

	ft_head_token(token_list);
	tree = ft_build_tree(token_list, envp);
	ft_clear_token_list(token_list);
	check = ft_check_commands(tree);
	if (check)
		ft_clear_tree(tree);
	if (check == 1)
	{
		ft_clear_env(*envp);
		rl_clear_history();
		exit(EC_ERRORS);
	}
	if (check & 2)
	{
		printf("WIJFWAFHAW");
		return ;
	}
	first_command = tree;
	treeprint(tree, 12);
	while (!(first_command->command))
		first_command = first_command->left;
	ft_exec(tree, ft_init_executor(tree), EX_WAIT);
	ft_clear_tree(tree);
}

	// /*
	// 	DEBUG SECTION
	// */
	// t_token *t;
	// t = tokens;
	// printf("------------- ACTUAL TOKEN LIST -------------\n");
	// while (t)
	// {
	// 	printf("[%s]->", t->str);
	// 	t = t->next;
	// }
	// printf("\n---------------------------------------------\n");
	// /*
	// 	END OF DEBUG
	// */