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

static void	signal_handler_inter(int signal)
{
	printf("\033[%dC", (int)(ft_strlen(rl_prompt) + ft_strlen(rl_line_buffer)) - 31);
	if (signal == 2)
	{
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	signal_handler_exec(int signal)
{
	if (signal == 2)
		printf("^C\n");
	else if (signal == 3)
		printf("^\\Quit (core dumped)\n");
}


void	toggle_signal(int toggle)
{
	static struct sigaction	action;
	struct termios		term_data;

	tcgetattr(0, &term_data);
	if (toggle)
	{
		// term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		// tcsetattr(0, 0, &term_data);

		// sigemptyset(&mask);
		// sigaddset(&mask, SIGQUIT);
		// action.sa_mask = mask;
		action.sa_flags = 0;
		action.sa_handler = &signal_handler_inter;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else
	{
		// action.sa_mask = mask;
		action.sa_flags = 0;
		action.sa_handler = &signal_handler_exec;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
}