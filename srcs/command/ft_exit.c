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

#include "../../minishell.h"

long long ft_atoi(char *str)
{
	int i = 0;
	int sign = 1;
	long long res = 0;

	while (str[i] == ' ' || str[i] == '\t') //changer whitespace
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

int ft_tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int is_digit(char *str)
{
	int i;
	char sign;

	while (*str == ' ' || *str == '\t') //changer whitespace
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
			|| (i == 18 && sign == '+' && str[i] >= '8')) //check if number is too big
			return (0);
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int ft_exit(char **args)
{
	int tablen;

	tablen = ft_tab_len(args);
	if (tablen == 0)
		exit(0);//get the exit status of the last command
	if (tablen >= 1 && is_digit(args[0]) == 0)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		exit(2);
	}
	if (tablen > 1 && is_digit(args[0]) == 1)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (tablen == 1 && args[0])
		exit(ft_atoi(args[0]) % 256);
	return (0);
}