/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:31:16 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/04 14:39:32 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_wildcard_string(void)
{
	char			*cwd;
	char			*wildcard;
	DIR				*cdir;
	struct dirent	*cdir_entry;

	wildcard = NULL;
	cwd = ft_get_pwd();
	if (!cwd)
		return (NULL);
	cdir = opendir(cwd);
	if (!cdir)
		perror("minishell");
	cdir_entry = readdir(cdir);
	while (cdir_entry)
	{
		wildcard = ft_strjoin(wildcard, cdir_entry->d_name, " ", 0b01);
		cdir_entry = readdir(cdir);
	}
	return (wildcard);
}
