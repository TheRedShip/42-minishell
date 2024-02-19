/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/19 22:54:21 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errors_end(t_error_code err, char *str, char *e)
{
	if (err == ERR_NOTCMD)
	{
		printf("%s", e);
		if (str)
			printf("%s", str);
		printf(": command not found\n");
	}
	if (err == ERR_SYNTAX)
		printf("%ssyntax error\n", e);
	free(e);
}

void	ft_error_message(t_error_code err, char *str)
{
	char	*e;
	char	*w;

	e = ft_strjoin(P_ERROR, P_ERR_TAIL, NULL, 0b00);
	w = ft_strjoin(P_WARNING, P_WNG_TAIL, NULL, 0b00);
	if (err == ERR_NOTSET)
		printf("%scd: %s not set\n", e, str);
	else if (err == ERR_NOFORD)
		printf("%s%s no such file or directory\n", e, str);
	else if (err == ERR_TMARGS)
		printf("%s%s: too many arguments\n", e, str);
	else if (err == ERR_NOTNUM)
		printf("%s%s: numeric argument required\n", e, str);
	else if (err == ERR_NOTVAL)
		printf("%sexport: `%s': not a valid identifier\n", e, str);
	else if (err == ERR_HDSTOP)
	{
		printf("%s here-document delimited by end-of", w);
		printf("-file, (wanted`%s')\n", str);
	}
	else if (err == ERR_DQSTOP)
		printf("%sunexpected EOF while looking for matching `%s\'\n", w, str);
	free(w);
	ft_errors_end(err, str, e);
}
