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

void start_execve(char *line, t_command *cmd)
{
	char **args;
	char **env;
	char *temp_command;
	pid_t pid;
	int status;

	args = ft_split(line, ' ');
	if (!args)
	{
		free(args);
		return ;
	}
	if (access(args[0], X_OK))
		temp_command = ft_get_path(args[0], cmd->envp);
	else
		temp_command = ft_strdup(args[0]);
	if (!temp_command)
	{
		ft_free_tab((void**)(args));
		return ;
	}
	toggle_signal(0);
	env = ft_get_var_strs(cmd->envp, 0);
	pid = fork();
	if (pid == 0)
	{
		execve(temp_command, args, env);
		perror("execve");
		free(temp_command);
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
	toggle_signal(1);
	free(temp_command);
	ft_free_tab((void **)(args));
	ft_free_tab((void **)(env));
}

void	builtin_cmd(char *line, t_envvar *envp, char *prompt) //FAUT FREE LA LINE si EXIT
{
	//t_command	*test = ft_init_command(0, 1, "env", envp);
	t_command	*test = ft_init_command(0, 1, line, envp);

	(void) envp;
	if (!ft_strncmp(line, "exit ", 5) || !ft_strncmp(line, "exit", 5))
		g_exit_code = ft_exit(test, prompt, envp);
	else if (!ft_strncmp(line, "echo ", 5) || !ft_strncmp(line, "echo", 5))
		g_exit_code = ft_echo(test);
	else if (!ft_strncmp(line, "env ", 4) || !ft_strncmp(line, "env", 4))
		g_exit_code = ft_env(test);
	else if (!ft_strncmp(line, "export ", 7) || !ft_strncmp(line, "export", 7))
		g_exit_code = ft_export(test);
	else if (!ft_strncmp(line, "unset ", 6) || !ft_strncmp(line, "unset", 6))
		g_exit_code = ft_unset(test);
	else if (!ft_strncmp(line, "pwd ", 4) || !ft_strncmp(line, "pwd", 4))
		g_exit_code = ft_pwd(test);
	else if (!ft_strncmp(line, "cd ", 3) || !ft_strncmp(line, "cd", 3))
		g_exit_code = ft_cd(test);
	else if (!ft_strncmp(line, "level", 6)) 										//DEBUG ONLY ne pas toucher
		printf("le level shell est %s\n", ft_get_var(envp, "SHLVL")->values[0]);
	else
		start_execve(line, test);
	ft_del_command(test);
}

void	ft_prompt(t_envvar *envp)
{
	char	*line;
	char	*prompt;

	prompt = ft_get_prompt_string(envp);
	line = readline(prompt);
	line = ft_quote_checker(line, QU_ZERO);
	if (!line)
	{
		printf("\n");
		ft_exit(NULL, prompt, envp);
	}
	add_history(line);
	line = parse_dollar(line, envp);
	// line = parse_quotes(line);
	builtin_cmd(line, envp, prompt);
	if (line)
		free(line);
	free(prompt);
}

char	*ft_trim_pwd(char *str)
{
	char	*lastb;

	lastb = ft_strrchr(str, '/');
	return (ft_strdup(lastb));
}

char	*ft_get_prompt_string(t_envvar *envp)
{
	static		t_envvar *save = NULL;
	char		*prompt;
	char		*pwd;

	if (envp)
		save = envp;
	if (ft_get_var(save, "PWD"))
	{
		pwd = ft_trim_pwd(ft_get_var(save, "PWD")->values[0]);
		pwd = ft_strjoin(pwd, " > ", 0, 1);
	}
	else
		pwd = ft_strdup(" > ");
	if (!g_exit_code)
		prompt = ft_strjoin(P_SUCCESS, P_TAIL, 0, 0);
	else
		prompt = ft_strjoin(P_FAIL, P_TAIL, 0, 0);
	prompt = ft_strjoin(prompt, pwd, 0, 3);
	return (prompt);
}
