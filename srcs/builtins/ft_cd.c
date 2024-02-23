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

// TODO REMETTRE CA AU GOUT DU JOUR CA COMMENCE A SE FAIRE VIEUX ET PAS A LA NORME

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
		ft_error_message(ERR_NOTSET, "HOME");
	if ((!argc || (argc == 1 && !ft_strcmp(argv[0], "~"))) && vars[0])
		chdir(vars[0]->values[0]);
	else if (argc == 1 && !ft_strcmp(argv[0], "-") && vars[1])
	{
		if (vars[1]->values)
		{
			ft_printf("\033\001[37;1m\002CD: moved to %s\001\033[0m\002\n", vars[1]->values[0]);
			chdir(vars[1]->values[0]);
		}
		else
			ft_error_message(ERR_NOTSET, "OLDPWD");
		if (!vars[1]->values)
			return (ERR_FAILED);
	}
	else if (argv[0])
	{
		if (chdir(argv[0]) == -1)
		{
			ft_error_message(ERR_NOFORD, argv[0]);
			return (ERR_FAILED);
		}
	}
	else
		return (ERR_FAILED);
	return (ERR_NOERRS);
}

int	ft_cd(t_command *cmd)
{
	int			argc;
	char		*newdir;
	t_envvar	**vars;

	argc = ft_tab_len(cmd->args);
	vars = ft_get_directory_vars(*(cmd->envp));
	if (!vars)
		return (ERR_FAILED);
	if (argc > 2)
	{
		free(vars);
		ft_error_message(ERR_TMARGS, "cd");
		return (ERR_FAILED);
	}
	if (ft_manage_cd(argc - 1, cmd->args + 1, vars))
	{
		free(vars);
		return (ERR_FAILED);
	}
	if (vars[2])
		ft_set_var(cmd->envp, "OLDPWD", ft_strdup(vars[2]->values[0]));
	newdir = ft_get_pwd();
	if (newdir)
		ft_set_var(cmd->envp, "PWD", newdir);
	free(vars);
	return (ERR_NOERRS);
}
