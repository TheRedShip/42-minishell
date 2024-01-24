/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 15:47:55 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *cmd, t_envvar *envp)
{
	int		i;
	char	*path;
	char	*bin;

	bin = ft_strjoin("/", cmd);
	while (ft_strncmp(envp->name, "PATH", 5))
		envp = envp->next;
	i = 0;
	path = ft_strjoin(envp->values[i++], bin);
	while (envp->values[i] && access(path, X_OK) == -1)
	{
		free(path);
		path = ft_strjoin(envp->values[i++], bin);
	}
	free(bin);
	return (path);
}

t_command	*ft_init_command(int input, int output, char *raw_cmd, t_envvar *envp)
{
	t_command	*new_command;
	char		**args;

	new_command = malloc(sizeof(t_command));
	new_command->infile = input;
	new_command->outfile = output;
	args = ft_split(raw_cmd, ' ');
	new_command->path = ft_get_path(args[0], envp);
	new_command->args = args;
	new_command->envp = NULL;
	return (new_command);
}

