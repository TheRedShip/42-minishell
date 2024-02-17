/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:52:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/17 15:46:54 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*ft_static_dq_holder(char *line, char *prompt, int dqfd, int ret)
{
	static char	*line_save = NULL;
	static char *prompt_save = NULL;
	static int	dqfd_save = -1;

	if (!line_save || line)
		line_save = line;
	if (!prompt_save || prompt)
		prompt_save = prompt;
	if (dqfd_save == -1 || dqfd)
		dqfd_save = dqfd;
	if (ret == 0b01)
		return (line_save);
	else if (ret == 0b10)
		return (prompt_save);
	else if (ret == 0b11)
		return ((char *)&dqfd_save);
	return (NULL);
}

char	*ft_open_dquote(int tmp_file_fd, t_quote_state qs)
{
	char	*line;
	char	*prompt;

	if (qs == QU_SINGLE)
	{
		prompt = ft_strjoin(P_SDQUOTE, P_ENDQUOTE, NULL, 0);
		ft_static_dq_holder(NULL, prompt, 0, 0b00);
		line = readline(prompt);
	}
	if (qs == QU_DOUBLE)
	{
		prompt = ft_strjoin(P_DDQUOTE, P_ENDQUOTE, NULL, 0);
		ft_static_dq_holder(NULL, prompt, 0, 0b00);
		line = readline(prompt);
	}
	write(tmp_file_fd, "\n", 1);
	free(prompt);
	write(tmp_file_fd, line, ft_strlen(line));
	return (line);
}

char	*ft_get_dquote_line(char *line, char *tmp_file, int status)
{
	char	*result;
	int		tmp_file_fd;

	tmp_file_fd = open(tmp_file, OPEN_READ);
	result = NULL;
	g_exit_code = WEXITSTATUS(status);
	line = get_next_line(tmp_file_fd);
	while (line)
	{
		result = ft_strjoin(result, line, NULL, 0b11);
		line = get_next_line(tmp_file_fd);
	}
	close(tmp_file_fd);
	unlink(tmp_file);
	return (result);
}

int	ft_get_dquote(char *line, t_envvar **env, char *tmp)
{
	int		tmp_file_fd;
	pid_t	quote_pid;

	quote_pid = fork();
	if (quote_pid == -1)
		return (-1);
	if (quote_pid == 0)
	{
		ft_signal_state(SIGHANDLER_DQU);
		tmp_file_fd = open(tmp, OPEN_CREATE, 0644);
		ft_static_dq_holder(NULL, NULL, tmp_file_fd, 0b00);
		rl_clear_history();
		ft_clear_env(*env);
		free(tmp);
		write(tmp_file_fd, line, ft_strlen(line));
		ft_quote_enforcer(&line, tmp_file_fd, QU_ZERO);
		free(line);
		ft_close_v(4, tmp_file_fd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	free(line);
	waitpid(quote_pid, &tmp_file_fd, 0);
	return (tmp_file_fd);
}

