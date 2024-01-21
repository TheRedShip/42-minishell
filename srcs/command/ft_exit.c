/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:15:41 by marvin            #+#    #+#             */
/*   Updated: 2024/01/16 16:15:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long ft_exit_atoi(char *str)
{
	int i = 0;
	int sign = 1;
	long long res = 0;

	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (sign == -1)
		return (256 - (res % 256));
	return (res % 256);
}

int is_digit(char *str)
{
	int i;
	char sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = '+';
	if (str[0] == '-' || str[0] == '+')
	{
		sign = str[0];
		str++;
	}
	i = 0;
	while (str[i])
	{
		if (i >= 19 || (i == 18 && sign == '-' && str[i] == '9')
			|| (i == 18 && sign == '+' && str[i] >= '8'))
			return (0);
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

void	real_exit(int exit_code, char *line, char **args)
{
 	rl_clear_history();
	free(line);
	ft_free_tab((void **)(args));
	exit(exit_code);
}

int ft_exit(char *line)
{
	char	**args;
	int		tablen;

	args = ft_split(line + 4, ' ');
	tablen = ft_tab_len(args);
	if (tablen == 0)
		real_exit(0, line, args);//get the exit status of the last command
	if (tablen >= 1 && is_digit(args[0]) == 0)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		real_exit(2, line, args);
	}
	if (tablen > 1 && is_digit(args[0]) == 1)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (tablen == 1 && args[0])
		real_exit(ft_exit_atoi(args[0]) % 256, line, args);
	return (0);
}
