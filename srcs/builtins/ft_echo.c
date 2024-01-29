/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:46:06 by marvin            #+#    #+#             */
/*   Updated: 2024/01/18 17:46:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_string(char **args)
{
	int i;
	char *string;

	string = NULL;
	i = 1;
	while (args[i])
	{
		if (string == NULL)
			string = ft_strdup(args[i]);
		else
			string = ft_strjoin(string, args[i], " ", 1);
		i++;
	}
	return (string);
}

int	skip_string(char **args)
{
	int i;
	int	j;
	int total;

	i = 0;
	total = 0;
	while(args[i])
	{
		j = 0;
		if (args[i][j] != '-' || (args[i][j] == '-' && args[i][j + 1] == '\0'))
			return (total);
		j++;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			return (total);
		total += j + 1;
		i++;
	}
	return (total);
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	trailing;
	char *string;
	if (!cmd->args[0])
	{
		printf("\n");
		return (0);
	}
	string = get_string(cmd->args);
	i = skip_string(cmd->args + 1);
	trailing = i == 0;
	while(i < (int)(ft_strlen(string)) && string[i])
	{
		write(cmd->outfile, string + i, 1);
		i++;
	}
	if (trailing)
		write(1, "\n", 1);
	free(string);
	return (0);
}
