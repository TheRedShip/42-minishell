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

void	start_execve(t_command *cmd)
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
		ft_clear_env(*(cmd->envp));
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

int	ft_quote_handler(char **line, char *prompt, t_envvar **envp, int status)
{
	char			*dquote_file;
	char			*history_line;
	t_quote_state	qs;

	if (!*line)
		return (EC_ERRORS);
	qs = QU_ZERO;
	history_line = *line;
	dquote_file = ft_get_temp_file(".dquote");
	if (ft_quote_syntax(*line, QU_ZERO))
	{
		status = ft_get_dquote(*line, prompt, envp, dquote_file);
		history_line = ft_get_dquote_line(*line, dquote_file, status);
	}
	add_history(history_line);
	free(dquote_file);
	*line = history_line;
	if (WEXITSTATUS(status) == 130)
		return (EC_FAILED);
	qs = ft_quote_syntax(*line, QU_ZERO);
	if (qs == QU_SINGLE)
		printf("minishell: unexpected EOF while looking for matching `\''\n");
	else if (qs == QU_DOUBLE)
		printf("minishell: unexpected EOF while looking for matching `\"'\n");
	return (EC_SUCCES);
}

void	ft_prompt_handle(t_envvar **envp)
{
	char	*line;
	char	*line_holder;
	char	*prompt;
	int		err_code;

	prompt = ft_get_prompt_string(*envp);
	line = readline(prompt);
	ft_signal_state(SIGHANDLER_IGN);
	err_code = ft_quote_handler(&line, prompt, envp, 0);
	if (err_code == EC_ERRORS)
	{
		ft_clear_env(*envp);
		ft_exit(NULL);
	}
	else if (err_code == EC_FAILED)
	{
		free(line);
		line = ft_strdup("");
		g_exit_code = 130;
	}
	ft_signal_state(SIGHANDLER_INT);
	line_holder = ft_replace_vars(*envp, line, QU_ZERO);
	free(line);
	line = line_holder;
	ft_prompt_tokenization(line, prompt, envp);
}

void	ft_prompt_tokenization(char *line, char *prompt, t_envvar **envp)
{
	t_token	*token_list;
	int		syntax;

	syntax = 0;
	token_list = ft_tokenizer(line, QU_ZERO);
	if (!token_list)
		return ;
	ft_format_tokens(&token_list, ft_get_var(*envp, "HOME"));
	ft_remove_braces(&token_list);
	if ((!ft_verify_token(token_list) || ft_quote_syntax(line, QU_ZERO)))
	{
		ft_putstr_fd("minishell: syntax error\n", 1);
		syntax++;
		g_exit_code = 2;
	}
	free(line);
	free(prompt);
	if (syntax)
		return ;
	ft_prompt_execution(token_list, envp);
}

void	ft_prompt_execution(t_token *token_list, t_envvar **envp) // REALLY LIGHT EXEC
{
	char		**tmp;
	t_node		*tree;
	t_node		*first_command;
	static int	(*builtins[7])(t_command *) = \
	{&ft_cd, &ft_pwd, &ft_echo, &ft_env, &ft_export, &ft_unset, &ft_exit};
	static char	*builtins_str[8] = \
	{"cd", "pwd", "echo", "env", "export", "unset", "exit", NULL};

	tree = ft_build_tree(token_list, envp);
	first_command = tree;
	while (!(first_command->command))
		first_command = first_command->left;
	tmp = builtins_str;
	while (*tmp)
	{
		if (!ft_strncmp(ft_backtrim(first_command->command->path, '/'), \
						*tmp, ft_strlen(*tmp) + 1))
		{
			g_exit_code = builtins[tmp - builtins_str](first_command->command);
			break ;
		}
		tmp++;
	}
	if (tmp == builtins_str + 7)
		start_execve(first_command->command);
	ft_clear_token_list(token_list);
	ft_clear_tree(tree);
}

// 	/*
// 		DEBUG SECTION
// 	*/
// 	t_token *t;
// 	t = tokens;
// 	printf("------------- ACTUAL TOKEN LIST -------------\n");
// 	while (t)
// 	{
// 		printf("[%s]->", t->str);
// 		t = t->next;
// 	}
// 	printf("\n---------------------------------------------\n");
// 	/*
// 		END OF DEBUG
// 	*/