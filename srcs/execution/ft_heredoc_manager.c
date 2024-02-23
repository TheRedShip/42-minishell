/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:59 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/23 10:15:35 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_heredoc_limit(t_token *tokens, t_envvar **envp)
{
	ft_error_message(ERR_HLIMIT, NULL);
	ft_clear_token_list(tokens);
	ft_clear_env(*envp);
	exit(ERR_ERRORS);
}

void	ft_parse_line(char **line, char **prompt, int hd_fd, int exp)
{
	int test;

	if (exp)
		ft_replace_vars(ft_update_env(NULL), line, QU_IGNORE, 1);
	test = write(hd_fd, *line, ft_strlen(*line));
	if (*prompt)
		write(hd_fd, "\n", 1);
	free(*line);
	*prompt = ft_strjoin(P_HEREDOC, P_HD_TAIL, NULL, 0b00);
	ft_hd_holder(*prompt, 1);
	*line = readline(*prompt);
	free(*prompt);
}

int	ft_heredoc_line(char *delim, char *hd_file, int hd_fd)
{
	char	*line;
	char	*prompt;
	int		exp;

	if (hd_fd == -1)
	{
		free(delim);
		return (ERR_FAILED);
	}
	line = ft_strdup("");
	prompt = NULL;
	exp = !(ft_strchr(delim, '"') || ft_strchr(delim, '\''));
	ft_dequote_string(&delim, QU_ZERO);
	ft_hd_holder(hd_file, 0);
	ft_hd_holder(delim, 1);
	ft_hd_holder((char *)&hd_fd, 2);
	while (line && ft_strncmp(line, delim, ft_strlen(delim) + 1) && !access(hd_file, F_OK))
		ft_parse_line(&line, &prompt, hd_fd, exp);
	free(delim);
	free(hd_file);
	if (!line)
		return (ERR_FAILED);
	free(line);
	return (ERR_NOERRS);
}

int	ft_heredoc_exit(char *delim, char *hd_file, int err_code)
{
	int	hd_fd;

	err_code = WEXITSTATUS(err_code);
	if (err_code == 1)
	{
		ft_dequote_string(&delim, QU_ZERO);
		ft_error_message(ERR_HDSTOP, delim);
	}
	else if (err_code == 130)
	{
		unlink(hd_file);
		free(delim);
		free(hd_file);
		g_exit_code = 130;
		return (OP_HDOCKO);
	}
	hd_fd = open(hd_file, OPEN_READ);
	unlink(hd_file);
	free(delim);
	free(hd_file);
	return (hd_fd);
}

int	ft_get_heredoc(char *delim, char *hd_file, t_node *root)
{
	pid_t	hd_pid;
	int		hd_fd;
	int		err_code;

	hd_pid = fork();
	if (hd_pid == -1)
		return (-1);
	if (hd_pid == 0)
	{
		ft_signal_state(SIGHANDLER_H_D);
		hd_fd = open(hd_file, OPEN_EXCL, 0644);
		ft_clear_tree(root);
		rl_clear_history();
		err_code = ft_heredoc_line(delim, hd_file, hd_fd);
		ft_clear_env(ft_update_env(NULL));
		ft_close_v(4, hd_fd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		exit(err_code);
	}
	waitpid(hd_pid, &err_code, 0);
	hd_fd = ft_heredoc_exit(delim, hd_file, err_code);
	return (hd_fd);
}
