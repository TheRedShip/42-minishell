/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:11:15 by marvin            #+#    #+#             */
/*   Updated: 2024/01/21 16:11:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

void start_execve(char *line, char **envp)
{
	char **args;
	char *temp_command;
	pid_t pid;

	toggle_signal(0);
	args = ft_split(line, ' ');
	pid = fork();
	if (pid == 0)
	{
		temp_command = str_add(args[0], "/bin/", 0);
		if (execve(temp_command, args, envp) == -1)
			perror("execve");
		free(temp_command);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		perror("fork");
	wait(NULL);
	toggle_signal(1);
	ft_free_tab((void **)(args));
}

void	builtin_cmd(char *line, t_envvar *envp, char **envpstring)
{
	(void) envp;
	if (!ft_strncmp(line, "exit ", 5) || !ft_strncmp(line, "exit", 5))
		g_exit_code = ft_exit(line);
	else if (!ft_strncmp(line, "echo ", 5) || !ft_strncmp(line, "echo", 5))
		g_exit_code = ft_echo(ft_split(line + 4, ' '));
	else if (!ft_strncmp(line, "pwd", 4))
		g_exit_code = ft_pwd();
	else if (!ft_strncmp(line, "cd ", 3) || !ft_strncmp(line, "cd", 3))
		g_exit_code = ft_cd(ft_split(line + 2, ' '));
	else
		start_execve(line, envpstring);
}

void	ft_prompt(t_envvar *envp, char **envpstring)
{
	char *line;

	line = readline("minishell:~$ ");
	if (!line)
		ft_exit(ft_strdup("exit"));
	add_history(line);
	line = parse_quotes(line);
	builtin_cmd(line, envp, envpstring);
	free(line);
}