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

int	ft_echo(t_command *cmd)
{
	int	i;
	int	trailing;
	char *string;
	char *args[] = {"echo", " ", "cc", "salut", NULL};
	(void) cmd;
	
	if (!args[0])
	{
		printf("\n");
		return (0);
	}

	string = NULL;
	i = 1;
	trailing = 1;
	(void) trailing;
	while (args[i])
	{
		if (string == NULL && ft_strlen(args[i]) != 0)
			string = ft_strdup(args[i]);
		else if (ft_strlen(args[i]) != 0)
			string = ft_strjoin(string, args[i], " ", 1);
		i++;
	}
	printf("%s\n", string);
	free(string);
	return (0);
}