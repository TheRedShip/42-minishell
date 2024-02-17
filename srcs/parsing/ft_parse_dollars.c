/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/17 13:01:06 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

// $ tout seul -> afficher
// $$ laisser
// $unknown -> ne PAS effacer mais ne pas remplacer
// $known -> REMPLACER

void	ft_quoted_skip(char **str, int len, t_quote_state *qs)
{
	while (*str && **str && (len-- > 0))
		ft_qs_update(*(*str)++, qs);
}

void	ft_insert_var(t_envvar *vars, char ***new, char *tmp, int cut)
{
	t_envvar	*var_ptr;
	char		*name;
	char		*var;
	int			len;

	len = 0;
	tmp++;
	if (*tmp == '?')
	{
		ft_strapp(new, ft_itoa(g_exit_code));
		return ;
	}
	while (*(tmp + len) && (ft_isalnum(*(tmp + len)) || *(tmp + len) == '_'))
		len++;
	name = ft_strndup(tmp, len);
	var_ptr = ft_get_var(vars, name);
	if (var_ptr)
		var = ft_get_varstring(ft_get_var(vars, name), 0, 0);
	else if (!cut)
		var = ft_strndup(tmp - 1, len + 1);
	else
		var = ft_strdup("");
	ft_strapp(new, var);
	free(name);
}

void	ft_replace_vars(t_envvar *vars, char **str, t_quote_state qs, int cut)
{
	int		len;
	char	*tmp;
	char	**new;

	tmp = *str;
	new = NULL;
	while (*tmp)
	{
		len = ft_strcspn(tmp, "$");
		ft_strapp(&new, ft_strndup(tmp, len));
		ft_quoted_skip(&tmp, len, &qs);
		if (!*tmp)
			break;
		if (qs != QU_SINGLE)
			ft_insert_var(vars, &new, tmp, cut);
		len = 0;
		tmp++;
		while (*(tmp + len) && (ft_isalnum(*(tmp + len)) || ft_strchr("_?", *(tmp + len))))
			ft_qs_update(*(tmp + len++), &qs);
		if (*(tmp - 1) != '?' && qs == QU_SINGLE)
			ft_strapp(&new, ft_strndup(tmp - 1, len + 1));
		tmp += len;
	}
	free(*str);
	*str = ft_strsjoin(new, NULL, 0b01);
}
