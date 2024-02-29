/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formatting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:42:43 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/28 20:56:19 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_quoted_split(char *str, char *sep)
{
	t_quote_state	qs;
	char			**new;
	char			*tmp;
	char			*hold;

	new = NULL;
	qs = QU_ZERO;
	if (!str || !sep || !*str)
		return (ft_strtab(ft_strdup("")));
	tmp = str;
	while (*str && *tmp)
	{
		tmp = str;
		while (*tmp && (!ft_strchr(sep, *tmp) || qs != QU_ZERO))
			ft_qs_update(*(tmp++), &qs);
		hold = ft_strndup(str, tmp - str);
		// ft_dequote_string(&hold, QU_ZERO);
		ft_strapp(&new, hold);
		str = tmp;
		while (*str && ft_strchr(sep, *str))
			str++;
	}
	return (new);
}

void	ft_command_checker(t_command *cmd)
{
	char	**new_args;
	char	**raw;
	char	**tmp;

	tmp = cmd->args;
	new_args = NULL;
	if (!tmp)
		return ;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '$'))
		{
			ft_replace_vars(*cmd->envp, tmp, QU_ZERO);
			raw = ft_quoted_split(*(tmp++), " ");
			ft_strtabjoin(&new_args, raw);
			continue ;
		}
		ft_dequote_string(tmp, QU_ZERO);
		ft_strapp(&new_args, ft_strdup(*(tmp++)));
	}
	free(cmd->path);
	if (*new_args)
		cmd->path = ft_get_path(*new_args, *cmd->envp);
	ft_free_tab((void **)cmd->args);
	cmd->args = new_args;
}
