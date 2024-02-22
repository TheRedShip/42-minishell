/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:51:52 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/15 18:51:52 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_h_ignore(int signal)
{
	(void) signal;
}

void	ft_h_inter(int signal)
{
	if (signal == 2)
	{
		g_exit_code = 130;
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void) signal;
}

void	ft_h_quote(int signal)
{
	int	fd;

	fd = 0;
	if (signal == 2)
	{
		printf("^C\n");
		free(ft_dq_holder(NULL, 0));
		free(ft_dq_holder(NULL, 1));
		fd = *(int *)ft_dq_holder(NULL, 2);
		ft_close_v(4, fd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		g_exit_code = 130;
		exit(130);
	}
	(void) signal;
}

void	ft_h_heredoc(int signal)
{
	int	fd;

	fd = 0;
	if (signal == 2)
	{
		printf("^C\n");
		unlink(ft_hd_holder(NULL, 0));
		ft_clear_env(ft_update_env(NULL));
		free(ft_hd_holder(NULL, 0));
		free(ft_hd_holder(NULL, 1));
		free(ft_hd_holder(NULL, 2));
		fd = *(int *)ft_hd_holder(NULL, 3);
		ft_close_v(4, fd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
		g_exit_code = 130;
		exit(130);
	}
	(void) signal;
}

void	ft_signal_state(int state)
{
	struct termios	termios_data;
	static void		(*handlers[4])(int) = {\
	ft_h_ignore, ft_h_inter, ft_h_quote, ft_h_heredoc};

	tcgetattr(0, &termios_data);
	if (!state)
		termios_data.c_lflag = termios_data.c_lflag | ECHOCTL;
	else
		termios_data.c_lflag = termios_data.c_lflag & (~ECHOCTL);
	tcsetattr(0, 0, &termios_data);
	signal(SIGINT, handlers[state]);
	signal(SIGQUIT, handlers[state]);
}
