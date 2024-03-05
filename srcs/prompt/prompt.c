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

t_error	ft_prompt_line(char **line, t_envvar **envp)
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

t_error	ft_to_tokens(t_token **tokens, char *line, t_envvar **envp)
{
	t_error	syntax;
	char	*err_token;

	syntax = (!!ft_quote_error(line, NULL, QU_ZERO) << 1);
	*tokens = ft_tokenizer(line, QU_ZERO);
	syntax |= ft_verify_token(*tokens, &err_token);
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
	ft_format_tokens(tokens, ft_get_var(*envp, "HOME"));
	ft_remove_braces(tokens);
	if (!*tokens)
		return (ERR_FAILED);
	free(line);
	if (syntax & 0b100)
		ft_heredoc_limit(*tokens, envp);
	return (ERR_NOERRS);
}

t_error	ft_to_tree_exec(t_token **tokens, t_node **tree, t_envvar **envp)
{
	t_executer	*exe;
	t_pid		*towait;
	int			err_code;
	static int	base_fd[2] = {0, 1};

	*tree = ft_build_tree(*tokens, envp);
	ft_clear_token_list(*tokens);
	ft_tree_holder(0, *tree);
	if (ft_heredoc_opening(*tree))
		return (ERR_HDSTOP);
	exe = ft_init_executer();
	ft_signal_state(SIGHANDLER_IGN);
	ft_exec_mux(*tree, (int *) base_fd, exe, EX_WAIT);
	while (exe->pids)
	{
		towait = ft_pid_pop(&(exe->pids));
		waitpid(towait->pid, &err_code, 0);
		g_exit_code = WEXITSTATUS(err_code);
		ft_command_exit(err_code);
		free(towait);
	}
	ft_signal_state(SIGHANDLER_INT);
	free(exe);
	return (ERR_NOERRS);
}

t_error	ft_heredoc_opening(t_node *tree)
{
	int	hd_done;

	hd_done = 0;
	if (ft_manage_heredocs(tree, &hd_done) == ERR_HDSTOP)
	{
		ft_close_tree_rec(tree);
		ft_clear_tree(tree);
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

void	ft_prompt_handler(t_envvar **envp)
{
	char		*line;
	int			first;
	t_token		*tokens;
	t_node		*tree;

	line = NULL;
	tokens = NULL;
	tree = NULL;
	first = 0;
	if (ft_prompt_line(&line, envp))
		return ;
	if (ft_to_tokens(&tokens, line, envp) || !tokens)
		return ;
	if (ft_to_tree_exec(&tokens, &tree, envp))
		return ;
	ft_close_tree_rec(tree);
	ft_clear_tree(tree);
}
