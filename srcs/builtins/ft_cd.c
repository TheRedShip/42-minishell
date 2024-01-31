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

t_envvar	**ft_get_directory_vars(t_envvar *envp)
{
	t_envvar	**vars;

	vars = malloc(4 * sizeof(t_envvar *));
	if (!vars)
		return (NULL);
	vars[0] = ft_get_var(envp, "HOME");
	vars[1] = ft_get_var(envp, "OLDPWD");
	vars[2] = ft_get_var(envp, "PWD");
	vars[3] = NULL;
	return (vars);
}

int	ft_manage_cd(int argc, char **argv, t_envvar **vars)
{
	if (!argc && !vars[0])
		printf("minishell: cd: HOME not set\n");
	if ((!argc || (argc == 1 && !ft_strcmp(argv[0], "~"))) && vars[0])
		chdir(vars[0]->values[0]);
	else if (argc == 1 && !ft_strcmp(argv[0], "-") && vars[1])
	{
		if (vars[1]->values)
		{
			printf("%s\n", vars[1]->values[0]);
			chdir(vars[1]->values[0]);
		}
		else
			printf("minishell: cd: OLDPWD not set\n");
		if (!vars[1]->values)
			return (EC_FAILED);
	}
	else if (argv[0])
	{
		if (chdir(argv[0]) == -1)
		{
			perror("minishell");
			return (EC_FAILED);
		}
	}
	else
		return(EC_FAILED);
	return (EC_SUCCES);
}

int	ft_cd(t_command *cmd)
{
	int			argc;
	char		*newdir;
	t_envvar	**vars;

	argc = ft_tab_len(cmd->args);
	vars = ft_get_directory_vars(*(cmd->envp));
	if (!vars)
		return (EC_FAILED);
	if (argc > 2)
	{
		free(vars);
		printf("minishell: cd: Too many arguments.\n");
		return (EC_FAILED);
	}
	if (ft_manage_cd(argc - 1, cmd->args + 1, vars))
	{
		free(vars);
		return (EC_FAILED);
	}
	if (vars[2])
		ft_set_var(cmd->envp, "OLDPWD", ft_strdup(vars[2]->values[0]));
	newdir = ft_get_pwd();
	if (newdir)
		ft_set_var(cmd->envp, "PWD", newdir);
	free(vars);
	return (EC_SUCCES);
}
