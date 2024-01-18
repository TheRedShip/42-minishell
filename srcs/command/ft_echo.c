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

#include "../../minishell.h"

int ft_echo(char **args)
{
	int	index;
	int	trailing;

	trailing = 1;
	index = 0;
	while (args[index])
	{
		if (ft_strcmp(args[index], "-n") == 0)
			trailing = 0;
		else
		{
			if (index != 0)
				printf(" ");
			printf("%s", args[index]);
		}
		index++;
	}
	if (trailing)
		printf("\n");
	return (0);
}