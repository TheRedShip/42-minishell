/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/04 23:21:44 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errors_end(t_error err, char *str)
{
	if (err == ERR_NOTCMD)
	{
		ft_dprintf(2, "%s", P_ERROR);
		if (str)
			ft_dprintf(2, "%s", str);
		ft_dprintf(2, ": command not found\n");
	}
	if (err == ERR_SYNTXQ)
		ft_dprintf(2, ES_SYNTXQ, P_ERROR, str);
	if (err == ERR_SYNTXT)
	{
		if (str)
			ft_dprintf(2, ES_SYNTXT, P_ERROR, str);
		else
			ft_dprintf(2, ES_SYNTXL, P_ERROR);
	}
	if (err == ERR_HLIMIT)
		ft_dprintf(2, ES_HLIMIT, P_ERROR);
	if (err == ERR_INVFDS)
		ft_dprintf(2, ES_INVFDS, P_ERROR, str);
	if (err == ERR_AMBRED)
		ft_dprintf(2, ES_AMBRED, P_ERROR, str);
	ft_dprintf(2, "\001\033[0m\002");
}

void	ft_error_message(t_error err, char *str)
{
	if (err == ERR_NOTSET)
		ft_dprintf(2, ES_NOTSET, P_ERROR, str);
	if (err == ERR_NOFORD)
		ft_dprintf(2, ES_NOFORD, P_ERROR, str);
	if (err == ERR_TMARGS)
		ft_dprintf(2, ES_TMARGS, P_ERROR, str);
	if (err == ERR_NOTNUM)
		ft_dprintf(2, ES_NOTNUM, P_ERROR, str);
	if (err == ERR_NOTVAL)
		ft_dprintf(2, ES_NOTVAL, P_ERROR, str);
	if (err == ERR_NOPERM)
		ft_dprintf(2, ES_NOPERM, P_ERROR, str);
	if (err == ERR_ISADIR)
		ft_dprintf(2, ES_ISADIR, P_ERROR, str);
	if (err == ERR_INVOPT)
		ft_dprintf(2, ES_INVOPT, P_ERROR, str);
	if (err == ERR_HDSTOP)
		ft_dprintf(2, ES_HDSTOP, P_WARNING, str);
	if (err == ERR_DQSTOP)
		ft_dprintf(2, ES_DQSTOP, P_WARNING, str);
	ft_errors_end(err, str);
}
