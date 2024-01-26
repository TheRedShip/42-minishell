/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:42:59 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 23:42:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static void	signal_handler_inter(int signal)
{
	printf("\033[%dC", (int)(ft_strlen(rl_prompt) + rl_point) - 31);
	if (signal == 2)
	{
		g_exit_code = 130;
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	signal_handler_exec(int signal)
{
	if (signal == 2)
		g_exit_code = 130;
	else if (signal == 3)
		g_exit_code = 131;
}

void	toggle_signal(int toggle)
{
	static struct sigaction	action;
	sigset_t mask;
	struct termios		term_data;

	tcgetattr(0, &term_data);
	if (toggle)
	{
		term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		tcsetattr(0, 0, &term_data);
		sigemptyset(&mask);
		sigaddset(&mask, SIGQUIT);
		action.sa_mask = mask;
		action.sa_flags = 0;
		action.sa_handler = &signal_handler_inter;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else
	{
		term_data.c_lflag = term_data.c_lflag | ECHOCTL;
		tcsetattr(0, 0, &term_data);
		action.sa_handler = signal_handler_exec;
		// action.sa_handler = SIG_IGN;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
}