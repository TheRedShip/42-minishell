/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:51:28 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/19 17:09:59 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dq_holder(char *addr, int type)
{
	static char	*prompt_save = NULL;
	static char	*line_save = NULL;
	static int	dqfd_save = -1;

	if (!line_save || (addr && type == 0))
		line_save = addr;
	if (!prompt_save || (addr && type == 1))
		prompt_save = addr;
	if (dqfd_save == -1 || (addr && type == 2))
		dqfd_save = *(int *)addr;
	if (type == 0)
		return (line_save);
	if (type == 1)
		return (prompt_save);
	return ((char *)&dqfd_save);
}

char	*ft_hd_holder(char *addr, int type)
{
	static char	*hd_file_save = NULL;
	static char	*prompt_save = NULL;
	static char	*delim_save = NULL;
	static int	hdfd_save = -1;

	if (!hd_file_save || (addr && type == 0))
		hd_file_save = addr;
	if (!prompt_save || (addr && type == 1))
		prompt_save = addr;
	if (!delim_save || (addr && type == 2))
		delim_save = addr;
	if (hdfd_save == -1 || (addr && type == 3))
		hdfd_save = *(int *)addr;
	if (type == 0)
		return (hd_file_save);
	if (type == 1)
		return (prompt_save);
	if (type == 2)
		return (delim_save);
	return ((char *)&hdfd_save);
}

t_node	*ft_tree_holder(int reset, t_node *root)
{
	static t_node	*tree_root = NULL;

	if (!tree_root || root)
		tree_root = root;
	if (reset)
		tree_root = NULL;
	return (tree_root);
}
