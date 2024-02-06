/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:31:16 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/06 17:08:07 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_verif_wildcard(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp == '*')
		tmp++;
	return (!*tmp && (tmp != str));
}

char	*ft_wildcard_string(void)
{
	char			*wildcard;
	DIR				*cdir;
	struct dirent	*cdir_entry;

	wildcard = ft_get_pwd();
	cdir = opendir(wildcard);
	free(wildcard);
	wildcard = NULL;
	if (!cdir)
		perror("minishell");
	cdir_entry = readdir(cdir);
	while (cdir_entry)
	{
		if (*(cdir_entry->d_name) != '.')
		{
			if (!wildcard)
				wildcard = ft_strjoin(wildcard, cdir_entry->d_name, NULL, 0b01);
			else
				wildcard = ft_strjoin(wildcard, cdir_entry->d_name, " ", 0b01);
		}
		cdir_entry = readdir(cdir);
	}
	free(cdir);
	return (wildcard);
}

void	ft_format_wildcard(char **str)
{
	char	**files;
	char	**tmp;
	char	*formatted;

	formatted = NULL;
	files = ft_split(*str, ' ');
	ft_sort_lowstrs_tab(files, ft_tab_len(files));
	tmp = files;
	while (*tmp)
	{
		if (!formatted)
			formatted = ft_strjoin(formatted, *(tmp++), NULL, 0b00);
		else
			formatted = ft_strjoin(formatted, *(tmp++), " ", 0b01);
	}
	free(*str);
	ft_free_tab((void **)files);
	*str = formatted;
}

void	ft_wildcard_token(t_token **head, t_token **tokens, t_token *prev)
{
	t_token *wctokens;
	t_token *tail;

	tail = (*tokens)->next;
	wctokens = ft_tokenizer((*tokens)->str, QU_ZERO);
	ft_add_token(&wctokens, tail);
	ft_del_token(*tokens);
	if (prev)
	{
		prev->next = wctokens;
		*tokens = wctokens;
	}
	else
		*head = wctokens;
}

void	ft_replace_wildcard(t_token **tokens, t_quote_state qs)
{
	t_token	*tmp;
	t_token	*prev;
	char	*wcs;

	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		ft_qs_update(*(tmp->str), &qs);
		if (qs == QU_ZERO && ft_verif_wildcard(tmp->str))
		{
			free(tmp->str);
			wcs = ft_wildcard_string();
			ft_format_wildcard(&wcs);
			tmp->str = ft_strdup(wcs);
			ft_wildcard_token(tokens, &tmp, prev);
			free(wcs);
		}
		prev = tmp;
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
}

// int main(void)
// {
// 	char *str = ft_strdup("salut * *********** *c *c* c*");
// 	t_token *tokens = ft_tokenizer(str, QU_ZERO);

// 	ft_replace_wildcard(&tokens, QU_ZERO);
// 	t_token *tmp = tokens;
// 	printf("%s\n", str);
	// while (tmp)
	// {
	// 	printf("[%s] ", tmp->str);
	// 	tmp = tmp->next;
	// }

// 	free(str);
// 	ft_clear_token_list(tokens);
// }
