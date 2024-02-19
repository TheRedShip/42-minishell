/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:38:34 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/19 22:46:28 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

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
	while (ft_isdigit(*str))
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
		return (!*str && str - tmp < 19);
	return (!*str && (str - tmp) && (str - tmp < 18));
}

void	ft_exit_manager(int exit_code, int ec, t_command *cmd)
{
	char	*msg;

	if (ec == ERR_NOTNUM)
	{
		msg = ft_strjoin("exit: ", cmd->args[1], NULL, 0b00);
		ft_error_message(ERR_NOTNUM, msg);
		free(msg);
	}
	if (ec == ERR_TMARGS)
	{
		ft_error_message(ERR_TMARGS, "exit");
		return ;
	}
	if (cmd)
	{
		ft_clear_env(*(cmd->envp));
		ft_del_command(cmd);
	}
	rl_clear_history();
	exit(exit_code);
}

int	ft_exit(t_command *cmd)
{
	int			argc;

	argc = 0;
	printf("exit\n");
	if (cmd)
		argc = ft_tab_len(cmd->args) - 1;
	if (!cmd || !argc)
		ft_exit_manager(g_exit_code, ERR_NOERRS, cmd);
	if (!ft_is_numeric(cmd->args[1]))
		ft_exit_manager(ERR_ERRORS, ERR_NOTNUM, cmd);
	if (argc > 1)
		ft_exit_manager(ERR_FAILED, ERR_TMARGS, cmd);
	else
		ft_exit_manager(ft_exit_atoi(cmd->args[1]), ERR_NOERRS, cmd);
	return (argc > 1);
}
