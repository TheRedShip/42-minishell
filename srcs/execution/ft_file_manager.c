/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:28 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/18 14:36:27 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_manage_file(t_token **tokens, int **fds)
// {
// 	int		state;

// 	state = !ft_strncmp((*tokens)->str, "<", 2) + 2 * !ft_strncmp((*tokens)->str, "<<", 3);
// 	printf("TESTING: state = [%d]\n", state);
// 	if (state)
// 	{
// 		printf("DEBUG :  OPENING INFILE: current = [%d], state = [%d]\n", (*fds)[0], state);
// 		if ((*fds)[0] > 2)
// 		{
// 			// printf("I CLOSE [%d]\n", (*fds)[0]);
// 			close((*fds)[0]);
// 		}
// 		if (state & 0b01)
// 			(*fds)[0] = open(((*tokens)->next)->str, OPEN_READ);
// 		else if (state & 0b10 && (*fds)[2] < 16)
// 		{
// 			(*fds)[0] = ft_get_heredoc(((*tokens)->next)->str);
// 			(*fds)[2]++;
// 		}
// 		else
// 			return (EC_FAILED);
// 		printf("FILE OPENED: fd = [%d]\n", (*fds)[0]);
// 	}
// 	state = !ft_strncmp((*tokens)->str, ">", 2) + 2 * !ft_strncmp((*tokens)->str, ">>", 3);
// 	// printf("TESTING: state = [%d]\n", state);
// 	if (state)
// 	{
// 		printf("DEBUG : OPENING OUTFILE: current = [%d], state = [%d]\n", (*fds)[1], state);
// 		if ((*fds)[1] > 2)
// 		{
// 			// printf("I CLOSE [%d]\n", (*fds)[1]);
// 			close((*fds)[1]);
// 		}
// 		if (state & 0b01)
// 			(*fds)[1] = open(((*tokens)->next)->str, OPEN_CREATE, 0644);
// 		else if (state & 0b10)
// 			(*fds)[1] = open(((*tokens)->next)->str, OPEN_APPEND, 0644);
// 		printf("FILE OPENED: fd = [%d]\n", (*fds)[1]);
// 	}
// 	(*tokens) = (*tokens)->next;
// 	return (EC_SUCCES);
// }

int	ft_heredoc_line(char *delim, char *hd_file, int hd_fd)
{
	char	*line;
	char	*prompt;

	line = ft_strdup("");
	prompt = NULL;
	ft_hd_holder(hd_file, 0);
	ft_hd_holder(delim, 2);
	ft_hd_holder((char *)&hd_fd, 3);
	while (line && ft_strncmp(line, delim, ft_strlen(delim)) && !access(hd_file, F_OK))
	{
		write(hd_fd, line, ft_strlen(line));
		if (prompt)
			write(hd_fd, "\n", 1);
		free(line);
		prompt = ft_strjoin(P_HEREDOC, P_HD_TAIL, NULL, 0b00);
		ft_hd_holder(prompt, 1);
		line = readline(prompt);
		free(prompt);
	}
	free(delim);
	free(hd_file);
	if (!line)
		return (EC_ERRORS);
	free(line);
	return (EC_SUCCES);
}

int	ft_heredoc_exit(char *hd_file, char *delim, int err_code)
{
	char	*line;
	int		hd_fd;

	hd_fd = open(hd_file, OPEN_READ);
	line = get_next_line(hd_fd);
	if (err_code == 130)
		return (OP_HDOCKO);
	unlink(hd_file);
	free(hd_file);
	free(delim);
	return (hd_fd);
}

int	ft_get_heredoc(char *delim, char *hd_file)
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
		ft_clear_token_list(ft_head_token(NULL));
		ft_clear_env(ft_update_env(NULL));
		rl_clear_history();
		err_code = ft_heredoc_line(delim, hd_file, hd_fd);
		ft_close_v(4, hd_fd, STDIN_FILENO, STDOUT_FILENO, 2);
		exit(err_code);
	}
	waitpid(hd_pid, &err_code, 0);
	if (WEXITSTATUS(err_code) == EC_ERRORS)
	{
		printf("%swarning here-document delimited by end-of-file", MINI);
		printf(" (wanted`%s')\n", delim);
	}
	return (ft_heredoc_exit(hd_file, delim, WEXITSTATUS(err_code)));
}

t_open_status	ft_manage_inputs(t_token **tokens, int *fd, int type)
{
	char	*hd_file;

	if (*fd > 2)
		close(*fd);
	if (type & 0b01)
		*fd = open((*tokens)->next->str, OPEN_READ);
	else if (type & 0b10)
	{
		hd_file = ft_get_temp_file(".heredoc", 16);
		ft_signal_state(SIGHANDLER_IGN);
		*fd = ft_get_heredoc(ft_strdup((*tokens)->next->str), hd_file);
		ft_signal_state(SIGHANDLER_INT);
	}
	(*tokens) = (*tokens)->next;
	if (*fd == OP_FILEKO)
	{
		printf("%s%s: No such file or directory", MINI, (*tokens)->str);
		return (OP_FILEKO);
	}	
	return (OP_FILEOK);
}

t_open_status	ft_manage_outputs(t_token **tokens, int *fd, int type)
{
	if (*fd > 2)
		close(*fd);
	if (type & 0b01)
		*fd = open((*tokens)->next->str, OPEN_CREATE, 0644);
	else if (type & 0b10)
		*fd = open((*tokens)->next->str, OPEN_APPEND, 0644);
	(*tokens) = (*tokens)->next;
	if (*fd == -1)
	{
		perror(MINI);
		return (OP_FILEXX);
	}
	return (OP_FILEKO);
}

t_open_status	ft_open_files(t_token **list, t_token **tk, int *stds)
{
	t_open_status	state;

	state = OP_FILEOK;
	if (!ft_strncmp((*tk)->str, ">", 2) || !ft_strncmp((*tk)->str, ">>", 3))
		state |= ft_manage_outputs(tk, &(stds[1]), ft_strlen((*tk)->str));
	else
		state |= ft_manage_inputs(tk, &(stds[0]), ft_strlen((*tk)->str));;
	if (state == OP_FILEXX)
		*list = (*tk)->next;
	return (state);
}
