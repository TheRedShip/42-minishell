/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/29 17:53:02 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_var_len(char *str)
{
	char *tmp;

	tmp = str;
	tmp++;
	if (!*tmp)
		return (1);
	if (ft_isdigit(*tmp) || (!ft_isalnum(*tmp) && !ft_strchr("_?", *tmp)))
		return (1);
	tmp++;
	while (*tmp && (ft_isalnum(*tmp) && !ft_strchr("_?", *tmp)))
		tmp++;
	return (tmp - str);
}

void	ft_quoted_skip(char **str, int *len, t_quote_state *qs)
{
	while (*str && **str && ((*len) > 0))
	{
		ft_qs_update(*(*str)++, qs);
		(*len)--;
	}
}

void	ft_insert_var(t_envvar *vars, char *start, char ***new, int len)
{
	t_envvar	*var_ptr;
	char		*name;

	if (*start && *(start + 1) == '?')
	{
		ft_strapp(new, ft_itoa(g_exit_code));
		return ;
	}
	start++;
	name = ft_strndup(start, len - 1);
	var_ptr = ft_get_var(vars, name);
	if (!var_ptr)
		ft_strapp(new, ft_strdup(""));
	else
		ft_strapp(new, ft_get_varstring(var_ptr, 0, 0));
	free(name);
}

void	ft_replace_vars(t_envvar *vars, char **str, t_quote_state qs)
{
	int		len;
	char	*tmp;
	char	**new;

	tmp = *str;
	new = NULL;
	if (!tmp)
		return ;
	while (*tmp)
	{
		len = ft_strcspn(tmp, "$");
		ft_strapp(&new, ft_strndup(tmp, len));
		ft_quoted_skip(&tmp, &len, &qs);
		if (!*tmp)
			break ;
		len = ft_var_len(tmp);
		if (qs != QU_SINGLE && len > 1)
			ft_insert_var(vars, tmp, &new, len);
		else
			ft_strapp(&new, ft_strndup(tmp, len));
		tmp += len;
	}
	free(*str);
	*str = ft_strsjoin(new, NULL, 0b01);
}
