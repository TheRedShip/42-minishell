/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:00:02 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 17:40:47 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(char *cmd, t_envvar *envp)
{
	int		i;
	char	*path;
	char	*bin;

	bin = ft_strjoin("/", cmd, 0);
	while (ft_strncmp(envp->name, "PATH", 5))
		envp = envp->next;
	i = 0;
	path = ft_strjoin(envp->values[i++], bin, 0);
	while (envp->values[i] && access(path, X_OK) == -1)
	{
		free(path);
		path = ft_strjoin(envp->values[i++], bin, 0);
	}
	free(bin);
	return (path);
}

