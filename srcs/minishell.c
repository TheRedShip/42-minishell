/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/20 16:01:16 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	char *line;
	while (1)
	{
		line = readline("minishell>");
		if (line && *line)
   			add_history(line);
		line = parse_quotes(line);
		if (!ft_strncmp(line, "exit", 4))
			exit(EXIT_SUCCESS);
		if (!ft_strncmp(line, "echo", 4))
			ft_echo(ft_split(line + 4, ' '));
		free(line);
	}
	return (0);
}