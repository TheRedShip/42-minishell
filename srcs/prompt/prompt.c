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

extern int g_exit_code;

void start_execve(char *line, char **envp)
{
	char **args;
	char *temp_command;
	pid_t pid;
	int status;

	args = ft_split(line, ' ');
	if (!args)
	{
		free(args);
		return ;
	}
	toggle_signal(0);
	pid = fork();
	if (pid == 0)
	{
		temp_command = str_add(ft_strdup(args[0]), "/bin/", 0);
		if (execve(temp_command, args, envp) == -1)
			perror("execve");
		free(temp_command);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("fork");
	waitpid(pid, &status, 0);
	if (g_exit_code < 130 || g_exit_code > 131)
		g_exit_code = WEXITSTATUS(status);
	toggle_signal(1);
	ft_free_tab((void **)(args));
}

void	builtin_cmd(char *line, t_envvar *envp, char **envpstring)
{
	(void) envp;
	if (!ft_strncmp(line, "exit ", 5) || !ft_strncmp(line, "exit", 5))
		g_exit_code = ft_exit(line);
	else if (!ft_strncmp(line, "echo ", 5) || !ft_strncmp(line, "echo", 5))
		g_exit_code = ft_echo(line + 5);
	else if (!ft_strncmp(line, "pwd", 4))
		g_exit_code = ft_pwd();
	else if (!ft_strncmp(line, "cd ", 3) || !ft_strncmp(line, "cd", 3))
		g_exit_code = ft_cd(ft_split(line + 2, ' '), envp);
	else if (!ft_strncmp(line, "level", 6)) 										//DEBUG ONLY ne pas toucher
		printf("le level shell est %s\n", ft_get_var(envp, "SHLVL")->values[0]);
	else
		start_execve(line, envpstring);
}

void	ft_prompt(t_envvar *envp, char **envpstring)
{
	char	*line;
	char	*prompt;

	prompt = ft_get_prompt_string(envp);
	line = readline(prompt);
	line = ft_quote_checker(line, QU_ZERO);
	printf("LIGNE = [%s]\n", line);
	if (!line)
		ft_exit(ft_strdup("exit"));
	add_history(line);
	line = parse_quotes(line);
	builtin_cmd(line, envp, envpstring);
	free(line);
	free(prompt);
}

char	*ft_get_prompt_string(t_envvar *envp)
{
	static		t_envvar *save = NULL;
	char		*prompt;
	char		*pwd;

	if (!save && envp)
		save = envp;
	if (ft_get_var(save, "PWD"))
		pwd = ft_strjoin(ft_get_var(save, "PWD")->values[0], " > ");
	else
		pwd = ft_strdup(" > ");
	if (!g_exit_code)
		prompt = ft_strjoin(P_SUCCESS, pwd);
	else
		prompt = ft_strjoin(P_FAIL, pwd);
	free(pwd);
	return (prompt);
}