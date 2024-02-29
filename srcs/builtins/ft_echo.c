/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:55:56 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/16 16:55:56 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_n_flag(char *str)
{
	if (!str || *str != '-')
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str == 'n')
		str++;
	return (!*str);
}

int	ft_echo(t_command *cmd)
{
	char	**args;
	char	*msg;
	int		trail;

	args = cmd->args + 1;
	msg = NULL;
	trail = 1;
	if (args)
	{
		while (*args && ft_is_n_flag(*args))
			args++;
		if (args != cmd->args + 1)
			trail = 0;
		msg = ft_strsjoin(args, ft_strdup(" "), 0b10);
		ft_printf("%s", msg);
	}
	if (trail)
		ft_printf("\n");
	free(msg);
	return (ERR_NOERRS);
}
