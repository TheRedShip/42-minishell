/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:35:12 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/20 15:35:12 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	cwd[65536];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}

int	ft_pwd(t_command *cmd)
{
	char	cwd[65536];

	(void) cmd;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (EC_FAILED);
	}
	return (EC_SUCCES);
}
