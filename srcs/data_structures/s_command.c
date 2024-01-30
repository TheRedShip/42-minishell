/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/30 14:51:05 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *cmd, t_envvar *envp)
{
	int		i;
	char	*path;
	char	*bin;

	bin = ft_strjoin("/", cmd, 0, 0);
	while (envp && ft_strncmp(envp->name, "PATH", 5))
	{
		printf("[%s] is not PATH\n", envp->name);
		envp = envp->next;
	}
	if (!envp)
		return (NULL);
	i = 0;
	path = ft_strjoin(envp->values[i++], bin, 0, 0);
	while (envp->values[i] && access(path, X_OK) == -1)
	{
		free(path);
		path = ft_strjoin(envp->values[i++], bin, 0, 0);
	}
	free(bin);
	if (!envp->values[i])
		free(path);
	if (!envp->values[i])
		return (NULL);
	return (path);
}

void	ft_del_command(t_command *cmd)
{
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
		close(cmd->outfile);
	free(cmd->path);
	ft_free_tab((void **)cmd->args);
	free(cmd);
}
