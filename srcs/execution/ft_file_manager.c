/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:28 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/02 16:10:50 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_code	ft_manage_heredocs(t_node *nd, int *hd)
{
	t_error_code	err;

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

t_error_code	ft_open_heredocs(t_command *cmd)
{
	t_error_code	err;
	t_redir			*tmp;
	char			*hd_file;

	err = ERR_NOERRS;
	tmp = cmd->redirs;
	while (tmp && cmd->heredoc != -1)
	{
		if (tmp->type == RD_HEREDOC)
		{
			hd_file = ft_get_temp_file(".heredoc", 16);
			if (cmd->heredoc > 2)
				close(cmd->heredoc);
			cmd->heredoc = ft_get_heredoc(ft_strdup(tmp->file), hd_file);
			if (cmd->heredoc == OP_HDOCKO)
				return (ERR_HDSTOP);
		}
		tmp = tmp->next;
	}
	return (cmd->heredoc == OP_FILEKO);
}

void	ft_open_file(t_command *cmd, char *file, int mode)
{
	int	*fd;

	if (mode == OPEN_READ)
		fd = &(cmd->infile);
	else
		fd = &(cmd->outfile);
	if (*fd > 2)
		close(*fd);
	if (mode != OPEN_READ && *fd != OP_FILEKO)
		*fd = open(file, mode, 0644);
	else if (*fd != -1)
		*fd = open(file, mode);
	if (*fd == -1)
		ft_error_message(ERR_NOFORD, file);
	free(file);
}

t_error_code	ft_open_outputs(t_command *cmd)
{
	t_redir			*tmp;

	tmp = cmd->redirs;
	while (tmp && cmd->outfile != OP_FILEKO)
	{
		if (tmp->type == RD_INFILES && access(tmp->file, R_OK))
			break ;
		if (tmp->type == RD_OUTPUTS)
			ft_open_file(cmd, ft_strdup(tmp->file), OPEN_CREATE);
		else if (tmp->type == RD_APPENDS)
			ft_open_file(cmd, ft_strdup(tmp->file), OPEN_APPEND);
		if (cmd->outfile != OP_FILEKO)
			tmp = tmp->next;
	}
	return (cmd->outfile == OP_FILEKO && access(tmp->file, R_OK));
}

void	ft_connect_input(t_command *cmd, int hd_last)
{
	if (hd_last)
	{
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		cmd->infile = cmd->heredoc;
	}
	else
	{
		if (cmd->heredoc > 2)
			close(cmd->heredoc);
	}
}

t_error_code	ft_open_inputs(t_command *cmd)
{
	t_redir	*tmp;
	int		hd_last;

	if (!cmd->redirs)
		return (ERR_NOERRS);
	tmp = cmd->redirs;
	hd_last = 0;
	while (tmp && cmd->infile != OP_FILEKO)
	{
		if (tmp->type == RD_INFILES)
		{
			hd_last = 0;
			ft_open_file(cmd, ft_strdup(tmp->file), OPEN_READ);
		}
		if (tmp->type != RD_OUTPUTS && tmp->type != RD_APPENDS)
			hd_last |= (tmp->type == RD_HEREDOC);
		tmp = tmp->next;
	}
	ft_connect_input(cmd, hd_last);
	return (cmd->infile == OP_FILEKO);
}
