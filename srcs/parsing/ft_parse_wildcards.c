/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:31:16 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/04 23:30:18 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_regex_wildcard(char *file, char *rule, char *tmp_f, char *tmp_r)
{
	char	*next;

	tmp_f = file;
	tmp_r = rule;
	while (*tmp_f)
	{
		next = NULL;
		while (*tmp_r == '*')
			tmp_r++;
		if (!*tmp_r)
			return (*(tmp_r - 1) == '*');
		if (!ft_strchr(tmp_r, '*'))
			next = ft_strrchr(tmp_f, *tmp_r);
		else if (tmp_r != rule || *tmp_r == *tmp_f)
			next = ft_strchr(tmp_f, *tmp_r);
		if (next)
			tmp_f += (next - tmp_f);
		else
			return (0);
		while (*tmp_f && *tmp_r && *tmp_r != '*' && *(tmp_f++) == *(tmp_r++))
			;
	}
	while (*tmp_r && *tmp_r == '*')
		tmp_r++;
	return (!*tmp_f && !*tmp_r);
}

char	**ft_wildcard_array(char *wcstr)
{
	char			*dir;
	char			**files;
	DIR				*cdir;
	struct dirent	*cdir_entry;

	dir = ft_get_pwd();
	cdir = opendir(dir);
	if (!cdir)
	{
		ft_error_message(ERR_NOFORD, dir);
		free(dir);
		return (NULL);
	}
	free(dir);
	cdir_entry = readdir(cdir);
	files = NULL;
	while (cdir_entry)
	{
		if (*(cdir_entry->d_name) != '.' && \
			ft_regex_wildcard(cdir_entry->d_name, wcstr, NULL, NULL))
			ft_strapp(&files, ft_strdup(cdir_entry->d_name));
		cdir_entry = readdir(cdir);
	}
	closedir(cdir);
	return (files);
}

void	ft_wildcard_token(t_token **head, t_token **tokens)
{
	t_token		*wctokens;
	t_token		*tail;
	t_token		*tmp;

	tail = (*tokens)->next;
	wctokens = ft_tokenizer((*tokens)->str, QU_ZERO);
	ft_add_token(&wctokens, tail);
	tmp = (*tokens)->prev;
	ft_del_token(*tokens);
	if (tmp)
	{
		tmp->next = wctokens;
		tmp = wctokens;
		while (tmp != tail)
			tmp = tmp->next;
		*tokens = tmp;
	}
	else
	{
		*head = wctokens;
		*tokens = tail;
	}
}

char	*ft_format_wildcard(char ***files)
{
	char	*formatted;

	formatted = NULL;
	ft_sort_lowstrs_tab(*files, ft_tab_len(*files));
	return (ft_strsjoin(*files, ft_strdup(" "), 0b10));
}

void	ft_replace_wildcard(char **str)
{
	char	**files;
	char	*wcs;
	char	*deq;

	deq = ft_strdup(*str);
	ft_dequote_string(&deq, QU_ZERO);
	files = ft_wildcard_array(deq);
	free(deq);
	if (files && *files)
	{
		free(*str);
		wcs = ft_format_wildcard(&files);
		*str = ft_strdup(wcs);
		free(wcs);
	}
	ft_free_tab((void **)(files));
}
