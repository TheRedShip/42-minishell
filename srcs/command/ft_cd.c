/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:03:33 by marvin            #+#    #+#             */
/*   Updated: 2024/01/18 23:03:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args)
{
	int	tab_len;

	tab_len = ft_tab_len(args);
	for (int i = 0; i < tab_len; i++){printf("%s\n", args[i]);}
	if (tab_len > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (tab_len == 1 && !ft_strcmp(args[0], "-"))
	{
		printf("salut");
		chdir(getenv("OLDPWD"));
		return (1);
	}
	if (tab_len == 0 || (tab_len == 1 && ft_strcmp(args[0], "~") == 0))
		return (0);
		// return (chdir("-"));
	if (chdir(args[0]) != 0)
	{
		perror(getenv("SHELL"));
		return (1);
	}
	return (0);
}