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

extern int g_exit_code;

static void	signal_handler(int signal)
{
	char	*prompt;

	prompt = ft_get_prompt_string(NULL);
	printf("%s", prompt);
	if (signal == 2)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	toggle_signal(int toggle)
{
	static struct sigaction	action;
	sigset_t			mask;
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
		action.sa_handler = &signal_handler;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else
	{
		action.sa_handler = SIG_IGN;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
}