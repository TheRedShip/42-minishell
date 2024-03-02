/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:58:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/01 18:53:01 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_init_redir(t_token *tmp)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	if (!ft_strncmp(tmp->str, ">>", 3))
		new_redir->type = RD_APPENDS;
	else if (!ft_strncmp(tmp->str, "<<", 3))
		new_redir->type = RD_HEREDOC;
	else if (!ft_strncmp(tmp->str, ">", 2))
		new_redir->type = RD_OUTPUTS;
	else if (!ft_strncmp(tmp->str, "<", 2))
		new_redir->type = RD_INFILES;
	new_redir->file = ft_strdup(tmp->next->str);
	ft_dequote_string(&(new_redir->file), QU_ZERO);
	new_redir->next = NULL;
	return (new_redir);
}

void	ft_add_redir(t_redir **redirs, t_redir *next)
{
	t_redir	*tmp;

	if (!redirs)
		return ;
	if (!*redirs)
	{
		*redirs = next;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
}

void	ft_clear_redir_list(t_redir *redir)
{
	if (!redir)
		return ;
	ft_clear_redir_list(redir->next);
	free(redir->file);
	free(redir);
}
