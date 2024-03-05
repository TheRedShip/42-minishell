/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 22:17:17 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *cmd, t_envvar *envp)
{
	int		i;
	char	*path;
	char	*bin;

	if (!cmd)
		return (ft_strdup(""));
	if (!*cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (envp && ft_strncmp(envp->name, "PATH", 5))
		envp = envp->next;
	if (!envp)
		return (ft_strjoin("/", ft_strdup(cmd), NULL, 0b10));
	bin = ft_strjoin("/", cmd, 0, 0b00);
	i = 0;
	path = ft_strjoin(envp->values[i++], bin, 0, 0);
	while (envp->values[i] && access(path, X_OK) == -1)
	{
		free(path);
		path = ft_strjoin(envp->values[i++], bin, 0, 0);
	}
	free(bin);
	return (path);
}

void	ft_del_command(t_command *cmd)
{
	ft_clear_redir_list(cmd->redirs);
	free(cmd->path);
	ft_free_tab((void **)cmd->args);
	free(cmd);
}
