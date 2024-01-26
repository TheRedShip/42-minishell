/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:38:34 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 08:43:46 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

long	ft_exit_atoi(char *str)
{
	long	n;
	int		sign;

	n = 0;
	sign = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*(str++) == '-');
	while (*str)
		n = n * 10 + (int){*(str++) - '0'};
	if (sign)
		return ((256 - n) % 256);
	return (n % 256);
}

int	ft_is_numeric(char *str)
{
	int		sign;
	char	*tmp;

	sign = 0;
	tmp = str;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		str++;
		sign = 1;
	}	
	while (ft_isdigit(*(str)))
		str++;
	if (sign)
		return (!*str && str - tmp < 18);
	return (!*str && (str - tmp) && (str - tmp < 19));
}

void	ft_exit_manager(int exit_code, int error_code, t_command *cmd)
{
	if (error_code == EC_NOTNUM)
		printf("exit: %s: numeric argument required\n", cmd->args[1]);
	if (error_code == EC_TOMAAR)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	rl_clear_history();
	exit(exit_code);
}

int ft_exit(t_command *cmd)
{
	int		argc;

	if (!cmd)
		ft_exit_manager(g_exit_code, EC_SUCCES, cmd);
	argc = ft_tab_len(cmd->args) - 1;
	printf("exit argc = %d\n", argc);
	if (!argc)
		ft_exit_manager(g_exit_code, EC_SUCCES, cmd);
	if (!ft_is_numeric(cmd->args[1]))
		ft_exit_manager(EC_ERRORS, EC_NOTNUM, cmd);
	if (argc > 1)
		ft_exit_manager(EC_FAILED, EC_TOMAAR, cmd);
	else
		ft_exit_manager(ft_exit_atoi(cmd->args[1]), EC_SUCCES, cmd);
	return (argc > 1);
}
