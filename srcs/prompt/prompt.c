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

void start_execve(char *line, char **envp)
{
	char **args;
	char *temp_command;
	pid_t pid;

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
	free(args);
}

void	builtin_cmd(char *line, char **envp)
{

	if (!ft_strncmp(line, "exit ", 5) || !ft_strncmp(line, "exit", 4))
		ft_exit(line);
	else if (!ft_strncmp(line, "echo ", 5) || !ft_strncmp(line, "echo\n", 5))
		ft_echo(ft_split(line + 5, ' '));
	else if (!ft_strncmp(line, "pwd\n", 4))
		ft_pwd();
	else if (!ft_strncmp(line, "cd ", 3) || !ft_strncmp(line, "cd\n", 3))
		ft_cd(ft_split(line + 3, ' '));
	else 
		start_execve(line, envp);
}

void	ft_prompt(char **envp)
{
	char *line;

	line = readline("minishell>");
	add_history(line);
	line = parse_quotes(line);
	builtin_cmd(line, envp);
	free(line);
}