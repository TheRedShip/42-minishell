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

void	ft_get_directory_vars(t_envvar *envp, t_envvar **vars)
{
	vars[0] = ft_get_var(envp, "HOME");
	vars[1] = ft_get_var(envp, "OLDPWD");
	vars[2] = ft_get_var(envp, "PWD");
	vars[3] = NULL;
}

t_error	ft_change_directory(char *target)
{
	if (!target)
		return (ERR_FAILED);
	if (chdir(target) == -1)
	{
		if (errno == EACCES)
			ft_error_message(ERR_NOPERM, target);
		else
			ft_error_message(ERR_NOFORD, target);
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

t_error	ft_manage_cd(int argc, char **argv, t_envvar **vars, int out)
{
	char	*target;

	target = NULL;
	if (!argc)
		target = *(vars[0]->values);
	else if (argc == 1)
	{
		if (!ft_strncmp(argv[0], "~", 2) && vars[0])
			target = *(vars[0]->values);
		else if (!ft_strncmp(argv[0], "-", 2) && vars[1])
		{
			if (vars[1]->values)
			{
				ft_dprintf(out, "\033[37;1m-> %s\033[0m\n", *(vars[1]->values));
				target = *(vars[1]->values);
			}
			else
				ft_error_message(ERR_NOTSET, "OLDPWD");
		}
		else
			target = argv[0];
	}
	return (ft_change_directory(target));
}

int	ft_cd(t_command *cmd)
{
	int			argc;
	char		*newdir;
	t_envvar	*vars[4];

	argc = ft_tab_len(cmd->args);
	if (argc > 2)
		ft_error_message(ERR_TMARGS, "cd");
	ft_get_directory_vars(*(cmd->envp), (t_envvar **) &vars);
	if (!(argc - 1) && !vars[0])
		ft_error_message(ERR_NOTSET, "HOME");
	else if (ft_manage_cd(argc - 1, cmd->args + 1, vars, cmd->outfile))
		return (ERR_FAILED);
	if (vars[2])
		ft_set_var(cmd->envp, "OLDPWD", ft_strdup(vars[2]->values[0]));
	else
		ft_error_message(ERR_NOTSET, "OLDPWD");
	newdir = ft_get_pwd();
	if (newdir)
		ft_set_var(cmd->envp, "PWD", newdir);
	else
		ft_error_message(ERR_NOTSET, "PWD");
	return (ERR_NOERRS);
}
