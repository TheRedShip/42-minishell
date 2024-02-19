/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:07:14 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/19 22:06:46 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_command *cmd)
{
	char	**tmp;

	if (ft_tab_len(cmd->args) < 2)
		return (ERR_FAILED);
	tmp = cmd->args + 1;
	while (*tmp)
		ft_remove_var(cmd->envp, *(tmp++));
	return (ERR_NOERRS);
}
