/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_dquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:52:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 00:28:47 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*ft_open_dquote(int tmp_file_fd, t_qstate qs)
{
	char	*line;

	if (qs == QU_SINGLE)
		line = readline(P_SDQUOTE);
	if (qs == QU_DOUBLE)
		line = readline(P_DDQUOTE);
	write(tmp_file_fd, "\n", 1);
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
		rl_catch_signals = 1;
		ft_signal_state(SIGHANDLER_DQU);
		tmp_file_fd = open(tmp, OPEN_EXCL, 0600);
		ft_dq_holder((char *)&tmp_file_fd, 1);
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

t_error	ft_quote_handler(char **line, t_envvar **envp, int status)
{
	char		*dquote_file;
	char		*history_line;
	char		*qs;

	if (!*line)
		return (ERR_ERRORS);
	history_line = *line;
	dquote_file = ft_get_temp_file(".dquote", 16);
	if (ft_quote_error(*line, NULL, QU_ZERO))
	{
		status = ft_get_dquote(*line, envp, dquote_file);
		history_line = ft_get_dquote_line(*line, dquote_file, status);
	}
	add_history(history_line);
	free(dquote_file);
	*line = history_line;
	if (WEXITSTATUS(status) == 130)
		free(*line);
	if (WEXITSTATUS(status) == 130)
		return (ERR_FAILED);
	qs = ft_strdup(" ");
	if (ft_quote_error(*line, qs, QU_ZERO))
		ft_error_message(ERR_DQSTOP, qs);
	free(qs);
	return (ERR_NOERRS);
}
