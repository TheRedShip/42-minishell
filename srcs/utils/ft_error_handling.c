/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 16:08:01 by rgramati         ###   ########.fr       */
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
		ft_dprintf(2, "%ssyntax error%s\n", P_ERROR, str);
	if (err == ERR_SYNTXT)
	{
		if (str)
		{
			ft_dprintf(2, "%ssyntax error near unexcepted token `%s'\n", \
					P_ERROR, str);
		}
		else
			ft_dprintf(2, "%ssyntax error\n", P_ERROR);
	}
	if (err == ERR_HLIMIT)
		ft_dprintf(2, "%smaximum here-document count exceeded\n", P_ERROR);
	ft_dprintf(2, "\001\033[0m\002");
}

void	ft_error_message(t_error err, char *str)
{
	if (err == ERR_NOTSET)
		ft_dprintf(2, "%scd: %s not set\n", P_ERROR, str);
	else if (err == ERR_NOFORD)
		ft_dprintf(2, "%s%s no such file or directory\n", P_ERROR, str);
	else if (err == ERR_TMARGS)
		ft_dprintf(2, "%s%s: too many arguments\n", P_ERROR, str);
	else if (err == ERR_NOTNUM)
		ft_dprintf(2, "%s%s: numeric argument required\n", P_ERROR, str);
	else if (err == ERR_NOTVAL)
		ft_dprintf(2, "%sexport: `%s': not a valid identifier\n", P_ERROR, str);
	else if (err == ERR_NOPERM)
		ft_dprintf(2, "%s%s: Permission denied\n", P_ERROR, str);
	else if (err == ERR_ISADIR)
		ft_dprintf(2, "%s%s: Is a directory\n", P_ERROR, str);
	else if (err == ERR_INVOPT)
		ft_dprintf(2, "%s%s: Invalid option\n", P_ERROR, str);
	else if (err == ERR_HDSTOP)
	{
		ft_dprintf(2, "%s here-document delimited by end-of", P_WARNING);
		ft_dprintf(2, "-file, (wanted `%s')\001\033[0m\002\n", str);
	}
	else if (err == ERR_DQSTOP)
		ft_dprintf(2, "%sunexpected EOF while looking for matching `%s\'\n", \
				P_WARNING, str);
	ft_errors_end(err, str);
}
