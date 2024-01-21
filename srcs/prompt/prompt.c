/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:11:15 by marvin            #+#    #+#             */
/*   Updated: 2024/01/21 16:11:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cmd(char *line)
{
	if (!ft_strncmp(line, "exit", 4))
        ft_exit(line);
    if (!ft_strncmp(line, "echo", 4))
        ft_echo(ft_split(line + 4, ' '));
}

void	ft_prompt(void)
{
	char *line;

	line = readline("minishell>");
	add_history(line);
	line = parse_quotes(line);
	builtin_cmd(line);
	free(line);
}