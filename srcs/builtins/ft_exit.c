/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:38:34 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 23:07:12 by rgramati         ###   ########.fr       */
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
	while (ft_isspace(*(str++)))
		;
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

void	ft_exit_manager(int exit_code, int ec, t_command *cmd, char *prompt)
{
	t_envvar	*tmp;

	if (ec == EC_NOTNUM)
		printf("exit: %s: numeric argument required\n", cmd->args[1]);
	if (ec == EC_TOMAAR)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	rl_clear_history();
	while (cmd->envp)
	{
		tmp = cmd->envp->next;
		ft_del_var(cmd->envp);
		cmd->envp = tmp;
	}
	ft_del_command(cmd);
	free(prompt);
	exit(exit_code);
}

int	ft_exit(t_command *cmd, char *prompt, t_envvar *envp)
{
	int			argc;
	t_command	*holder;

	holder = NULL;
	if (envp)
		holder = ft_init_command(0, 0, "exit", envp);
	if (!cmd)
		ft_exit_manager(g_exit_code, EC_SUCCES, holder, prompt);
	argc = ft_tab_len(cmd->args) - 1;
	printf("exit\n");
	if (!argc)
		ft_exit_manager(g_exit_code, EC_SUCCES, cmd, prompt);
	if (!ft_is_numeric(cmd->args[1]))
		ft_exit_manager(EC_ERRORS, EC_NOTNUM, cmd, prompt);
	if (argc > 1)
		ft_exit_manager(EC_FAILED, EC_TOMAAR, cmd, prompt);
	else
		ft_exit_manager(ft_exit_atoi(cmd->args[1]), EC_SUCCES, cmd, prompt);
	return (argc > 1);
}
