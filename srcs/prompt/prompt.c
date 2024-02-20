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
extern int	DEBUG;

void	ft_display_token_list(t_token *tokens)
{
		/*
		DEBUG SECTION
	*/
	t_token *t;
	t = tokens;
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
			ft_error_message(ERR_NOTCMD, *cmd->args);
		else
			ft_error_message(ERR_NOTCMD, NULL);
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
		rl_clear_history();
		test = ft_process_redirs(cmd, ex);
		if (test == 2)
		{
			ft_free_tab((void **)env);
			ft_clear_env(*(cmd->envp));
			ft_clear_tree(ex->root);
			ft_del_executor(ex);
			exit(ERR_FAILED);
		}
		ft_close_executor(ex);
		execve(cmd->path, cmd->args, env);
		perror("execve");
		exit(ERR_FAILED);
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

t_error_code	ft_prompt_line(t_envvar **envp, char **line)
{
	char	*prompt;
	int		err_code;

	prompt = ft_get_prompt_string(*envp);
	*line = readline(prompt);
	free(prompt);
	if (*line && !ft_isnt_empty(*line))
	{
		free(*line);
		return (ERR_FAILED);
	}
	ft_signal_state(SIGHANDLER_IGN);
	err_code = ft_quote_handler(line, envp, 0);
	ft_signal_state(SIGHANDLER_INT);
	if (err_code == ERR_ERRORS)
	{
		ft_clear_env(*envp);
		ft_exit(NULL);
	}
	else if (err_code == ERR_FAILED || !*line)
	{
		g_exit_code = 130;
		return (ERR_DQSTOP);
	}
	return (ERR_NOERRS);
}

t_error_code	ft_to_tokens(t_token **tokens, char *line, t_envvar **envp)
{
	t_error_code	syntax;
	char			*err_token;

	syntax = (!!ft_quote_error(line, QU_ZERO) << 1);
	*tokens = ft_tokenizer(line, QU_ZERO);
	syntax |= ft_verify_token(*tokens, &err_token);
	if (!*tokens)
		return (ERR_FAILED);
	ft_format_tokens(tokens, ft_get_var(*envp, "HOME"));
	ft_remove_braces(tokens);
	if (DEBUG)
		ft_display_token_list(*tokens);
	if (syntax & 0b011)
	{
		if (syntax & 0b10)
			ft_error_message(ERR_SYNTXQ, ": unexcepted end of file");
		else
			ft_error_message(ERR_SYNTXT, err_token);
		ft_clear_token_list(*tokens);
		free(line);
		g_exit_code = 2;
		return (ERR_FAILED);
	}
	free(line);
	if (syntax & 0b100)
		ft_heredoc_limit(*tokens, envp);
	return (ERR_NOERRS);
}

t_error_code	ft_to_tree(t_token **tokens, t_node **tree, t_envvar **envp)
{
	*tree = ft_build_tree(*tokens, envp);
	ft_clear_token_list(*tokens);
	if (ft_check_commands(*tree))
		return (ERR_FAILED);
	if (DEBUG)
		treeprint(*tree, 0);
	return (ERR_NOERRS);
}

t_error_code	ft_file_opening(t_node *tree, t_envvar **envp)
{
	int	hd_done;

	hd_done = 1;
	ft_signal_state(SIGHANDLER_IGN);
	if (ft_open_heredocs(tree, tree, &hd_done))
	{
		ft_close_tree_rec(tree);
		ft_clear_tree(tree);
		ft_signal_state(SIGHANDLER_INT);
		return (ERR_FAILED);
	}
	ft_signal_state(SIGHANDLER_INT);
	if (ft_open_outputs(tree))
	{
		ft_close_tree_rec(tree);
		ft_clear_tree(tree);
		ft_clear_env(*envp);
		rl_clear_history();
		exit(ERR_FAILED);
	}
	return (ERR_NOERRS);
}


void	ft_prompt_handler(t_envvar **envp)
{
	char	*line;
	t_token	*tokens;
	t_node	*tree;

	line = NULL;
	tokens = NULL;
	tree = NULL;
	if (ft_prompt_line(envp, &line))
		return ;
	if (ft_to_tokens(&tokens, line, envp))
		return ;
	if (ft_to_tree(&tokens, &tree, envp))
	{
		ft_clear_tree(tree);
		exit(ERR_FAILED);
	}
	if (ft_file_opening(tree, envp))
		return ;
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
