/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formatting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:42:43 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/17 17:13:38 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command_checker(t_command *cmd)
{
	char	**new_args;
	char	**raw;
	char	**tmp;

	tmp = cmd->args;
	new_args = NULL;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '$'))
		{
			ft_replace_vars(*cmd->envp, tmp, QU_ZERO, 1);
			raw = ft_split(*(tmp++), ' ');
			ft_strtabjoin(&new_args, raw);
		}
		else
		{
			ft_dequote_string(tmp, QU_ZERO);
			ft_strapp(&new_args, ft_strdup(*(tmp++)));
		}
	}
	free(cmd->path);
	if (*new_args)
		cmd->path = ft_get_path(*new_args, *cmd->envp);
	ft_free_tab((void **)cmd->args);
	cmd->args = new_args;
}
