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

#include "../../minishell.h"

int ft_cd(char **args)
{
	int	tab_len;

	tab_len = ft_tab_len(args);
	if (tab_len > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (tab_len == 0 || (tab_len == 1 && ft_strcmp(args[0], "~") == 0))
		return (0);
		// return (chdir("-"));
	if (chdir(args[0]) != 0)
	{
		fprintf( stderr, "minishell: cd: %s: No such file or directory\n", args[0]);
		return (1);
	}
	return (0);
}