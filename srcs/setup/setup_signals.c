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
	printf("\033[%dC", (int) ft_strlen(rl_prompt) + rl_point - 39);
	if (signal == 2)
	{
		g_exit_code = 130;
		printf("^C\n");
		rl_replace_line("", 0);
        // printf("%s", ft_get_prompt_string(NULL));
		rl_on_new_line();
		rl_redisplay();
	}
}

// static void	signal_handler_exec(int signal)
// {
// 	if (signal == 2)
// 	{
// 		printf("Quit core dumped\n");
// 		g_exit_code = 130;
// 	}
// 	else if (signal == 3)
// 	{
// 		printf("\n");
// 		g_exit_code = 131;
// 	}
// }

void	ign(int signal)
{
	(void)signal;
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