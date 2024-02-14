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

void	ft_interactive_handler(int signal)
{
    // char    *prompt;
	printf("\001\033[%dC\002", (int) ft_strlen(rl_prompt) + rl_point - 39);
	if (signal == 2)
	{
		g_exit_code = 130;
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_dquote_handler(int signal)
{
	printf("\001\033[%dC\002", (int) ft_strlen(rl_prompt) + rl_point - 39);
	(void) signal;
}

void	ign(int signal)
{
	(void) signal;
}

void	toggle_signal(int toggle)
{
	struct termios	term_data;

	tcgetattr(0, &term_data);
	if (toggle == 1)
	{
		term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		tcsetattr(0, 0, &term_data);
		signal(SIGINT, ft_interactive_handler);
		signal(SIGQUIT, ft_interactive_handler);
	}
	else if (toggle == 0)
	{
		term_data.c_lflag = term_data.c_lflag | ECHOCTL;
		tcsetattr(0, 0, &term_data);
		signal(SIGINT, ign);
		signal(SIGQUIT, ign);
	}
	else if (toggle == 2)
	{
		term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
		tcsetattr(0, 0, &term_data);
		signal(SIGINT, ft_dquote_handler);
		signal(SIGQUIT, ft_dquote_handler);
	}
}
