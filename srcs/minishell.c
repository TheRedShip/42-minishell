/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/21 15:32:28 by marvin           ###   ########.fr       */
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
		// if (line && *line)
   			// add_history(line);
		line = parse_quotes(line);
		if (!ft_strncmp(line, "exit", 4))
			exit(EXIT_SUCCESS);
		if (!ft_strncmp(line, "echo", 4))
			ft_echo(ft_split(line + 4, ' '));
		free(line);
	}
	return (0);
}