/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formatting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:42:43 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/17 15:04:09 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command_checker(t_command *cmd)
{
	char	*raw;
	char	**new_args;
	char	**tmp;

	raw = ft_strsjoin(cmd->args, " ", 0b00);
	if (ft_strchr(raw, '$'))
	{
		free(cmd->path);
		ft_free_tab((void **)cmd->args);
		ft_replace_vars(*cmd->envp, &raw, QU_ZERO, 1);
		new_args = ft_split(raw, ' ');
		if (new_args)
			cmd->path = ft_get_path(*new_args, *cmd->envp);
		cmd->args = new_args;
	}
	else
	{
		tmp = cmd->args;
		while (*tmp)
			ft_dequote_string(&(*(tmp++)), QU_ZERO);
	}
	// ft_command_wc_checker(cmd);
	free(raw);
}
