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

static void	signal_handler(int signal)
{
    // char    *prompt;

	printf("\001\033[%dC\002", (int) ft_strlen(rl_prompt) + rl_point - 39);
	if (signal == 2)
	{
		g_exit_code = 130;
        // prompt = ft_get_prompt_string(ft_update_env(NULL));
        // printf("%s", prompt);
		printf("^C\n");
		rl_replace_line("", 0);
        rl_on_new_line();
		rl_redisplay();
	}
}

void	ign(int signal)
{
	(void)signal;
}

void    testdquote(int signal)
{
	printf("\001\033[%dC\002", (int) ft_strlen(rl_prompt) + rl_point - 39);
	(void) signal;
}

void    toggle_signal(int toggle)
{
    struct termios        term_data;

    tcgetattr(0, &term_data);
    if (toggle)
    {
        term_data.c_lflag = term_data.c_lflag & (~ECHOCTL);
        tcsetattr(0, 0, &term_data);
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);
    }
    else
    {
        term_data.c_lflag = term_data.c_lflag | ECHOCTL;
        tcsetattr(0, 0, &term_data);
        signal(SIGINT, ign);
        signal(SIGQUIT, ign);
    }
}