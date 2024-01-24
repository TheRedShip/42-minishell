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

int	ft_cd(char **argv, t_envvar *envp)
{
	int			argc;
	char		*newdir;
	t_envvar	*vars[4];
	
	argc = ft_tab_len(argv);
	vars[0] = ft_get_var(envp, "HOME");
	vars[1] = ft_get_var(envp, "OLDPWD");
	vars[2] = ft_get_var(envp, "PWD");
	vars[3] = ft_get_var(envp, "SHELL");
	if (argc > 1)
	{
		printf("minishell: cd: Too many arguments.\n");
		return (1);	
	}
	else
	{
		if ((!argc || (argc == 1 && !ft_strcmp(argv[0], "~"))) && vars[0])
			chdir(vars[0]->values[0]);
		else if (argc == 1 && !ft_strcmp(argv[0], "-") && vars[1] && vars[2])
			chdir(vars[1]->values[0]);
		else
		{
			if (chdir(argv[0]) && vars[3])
			{
				perror(vars[3]->values[0]);
				return (1);
			}
		}
	}
	ft_set_var(envp, "OLDPWD", vars[2]->values[0]);
	newdir = ft_get_pwd();
	ft_set_var(envp, "PWD", newdir);
	free(newdir);
	ft_free_tab((void **)argv);
	return (0);
}
