/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:42:43 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 00:23:40 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_quoted_split(char *str, char *sep)
{
	t_qstate	qs;
	char		**new;
	char		*tmp;
	char		*hold;

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
		ft_strapp(&new, hold);
		str = tmp;
		while (*str && ft_strchr(sep, *str))
			str++;
	}
	return (new);
}

void	ft_args_updater(t_command *cmd)
{
	char	**new_args;
	char	**raw;
	char	**tmp;

	tmp = cmd->args;
	new_args = NULL;
	while (tmp && *tmp)
	{
		if (ft_strchr(*tmp, '$'))
		{
			ft_replace_vars(*cmd->envp, tmp, QU_ZERO);
			if (**tmp)
			{
				raw = ft_split(*tmp, ' ');
				ft_strtabjoin(&new_args, raw);
			}
			tmp++;
			continue ;
		}
		if (ft_strncmp(*cmd->args, "export", 7))
			ft_dequote_string(tmp, QU_ZERO);
		ft_strapp(&new_args, ft_strdup(*(tmp++)));
	}
	ft_free_tab((void **)cmd->args);
	cmd->args = new_args;
}

void	ft_path_updater(t_command *cmd)
{
	free(cmd->path);
	cmd->path = NULL;
	if (cmd->args && *cmd->args)
		cmd->path = ft_get_path(*cmd->args, *(cmd->envp));
}

t_error	ft_command_updater(t_command *cmd)
{
	char	**tmp;

	ft_args_updater(cmd);
	tmp = cmd->args;
	while (tmp && *tmp)
	{
		if (ft_verify_wildcard(*tmp, QU_ZERO))
			ft_replace_wildcard(tmp++);
		else
			ft_dequote_string(tmp++, QU_ZERO);
	}
	ft_path_updater(cmd);
	if (!cmd->path && !cmd->redirs)
		return (ERR_NOTCMD);
	return (ERR_NOERRS);
}

t_error	ft_manage_heredocs(t_node *nd, int *hd)
{
	t_error	err;

	if (!nd)
		return (ERR_ERRORS);
	err = ERR_NOERRS;
	if (*hd)
		return (ERR_HDSTOP);
	if (!nd->command)
	{
		err |= ft_manage_heredocs(nd->left, hd);
		err |= ft_manage_heredocs(nd->right, hd);
		return (err);
	}
	err = ft_open_heredocs(nd->command);
	return (err);
}
