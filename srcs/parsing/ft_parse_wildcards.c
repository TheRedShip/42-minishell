/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 13:31:16 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/12 00:35:41 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif_wildcard(char *str)
{
	char			*tmp;
	t_quote_state	qs;

	tmp = str;
	qs = QU_ZERO;
	if (!str || !*str)
		return (0);
	while (*tmp && ((*tmp == '*') ^ (qs != QU_ZERO)))
	{
		ft_qs_update(*tmp, &qs);
		tmp++;
	}
	return (!*tmp && (tmp != str));
}

//en construction faut gerer les wildcards un peu plus pousses sinon cest pas bo.
// int	ft_wc_rule(char *dname, char *wcrule)
// {
// 	char	*rule;
// 	char	*tmp;

// 	rule = ft_strnstr(dname, ft_strrchr(wcrule, '*') + 1, ft_strlen(dname));
// 	if (!rule)
// 		return (EC_FAILED);
// 	tmp = ;
// 	while (*tmp &&)

// }

char	*ft_wildcard_string(char *wcstr)
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
		if (*(cdir_entry->d_name) != '.' && \
			!ft_wc_rule(cdir_entry->d_name, wcstr))
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

// int main(void)
// {
// 	char *str = ft_strdup("salut * *********** *c *c* c*");
// 	t_token *tokens = ft_tokenizer(str, QU_ZERO);

// 	ft_replace_wildcard(&tokens, QU_ZERO);
// 	t_token *tmp = tokens;
// 	printf("%s\n", str);
// 	while (tmp)
// 	{
// 		printf("[%s] ", tmp->str);
// 		tmp = tmp->next;
// 	}

	// free(str);
	// ft_clear_token_list(tokens);
// }
