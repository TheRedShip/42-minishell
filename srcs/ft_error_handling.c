/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/20 22:08:09 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errors_end(t_error_code err, char *str)
{
	if (err == ERR_NOTCMD)
	{
		printf("%s", P_ERROR);
		if (str)
			printf("%s", str);
		printf(": command not found\n");
	}
	if (err == ERR_SYNTXQ)
		printf("%ssyntax error%s\n", P_ERROR, str);
	if (err == ERR_SYNTXT)
	{
		if (str)
			printf("%ssyntax error near unexcepted token `%s'\n", P_ERROR, str);
		else
			printf("%ssyntax error\n", P_ERROR);
	}
	if (err == ERR_HLIMIT)
		printf("%smaximum here-document count exceeded\n", P_ERROR);
	printf("\001\033[0m\002");
}

void	ft_error_message(t_error_code err, char *str)
{
	if (err == ERR_NOTSET)
		printf("%scd: %s not set\n", P_ERROR, str);
	else if (err == ERR_NOFORD)
		printf("%s%s no such file or directory\n", P_ERROR, str);
	else if (err == ERR_TMARGS)
		printf("%s%s: too many arguments\n", P_ERROR, str);
	else if (err == ERR_NOTNUM)
		printf("%s%s: numeric argument required\n", P_ERROR, str);
	else if (err == ERR_NOTVAL)
		printf("%sexport: `%s': not a valid identifier\n", P_ERROR, str);
	else if (err == ERR_HDSTOP)
	{
		printf("%s here-document delimited by end-of", P_WARNING);
		printf("-file, (wanted`%s')\001\033[0m\002\n", str);
	}
	else if (err == ERR_DQSTOP)
		printf("%sunexpected EOF while looking for matching `%c\'\n",\
				P_WARNING, *str);
	ft_errors_end(err, str);
}
