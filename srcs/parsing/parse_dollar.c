/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/02 19:05:14 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*ft_insert_var(t_envvar *vars, char *result, char *str, int *len)
{
	char	*tmp;
	char	*var;
	char	*value;

	tmp = str;
	if (!ft_strlen(str))
		return (result);
	if (ft_strlen(str) == 1 || (str && ft_isspace(*(str + 1))))
		*len = 1;
	if (ft_strlen(str) == 1 || (str && ft_isspace(*(str + 1))))
		return (ft_strjoin(result, "$", NULL, 0b01));
	if (*(str + 1) == '?')
		*len = 2;
	if (*(str + 1) == '?')
		return (ft_strjoin(result, ft_itoa(g_exit_code), NULL, 0b11));
	str++;
	while (!ft_strchr(" $'\"\n", *str))
		str++;
	*len = str - tmp;
	var = ft_strndup(tmp + 1, *len - 1);
	value = ft_get_varstring(ft_get_var(vars, var), 0, 0);
	free(var);
	var = ft_strjoin(result, value, NULL, 0b11);
	return (var);
}

char	*ft_replace_vars(t_envvar *vars, char *str, t_quote_state qs)
{
	char			*result;
	int				len;

	len = ft_strchr(str, '$') - str;
	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strndup(str, len);
	while (len)
	{
		ft_qs_update(*(str++), &qs);
		len--;
	}
	if (qs != QU_SINGLE && str)
		result = ft_insert_var(vars, result, str, &len);
	else
	{
		while (!ft_strchr(" $'\"\n", *(str + len + 1)))
			len++;
		result = ft_strjoin(result, ft_strndup(str, ++len), NULL, 0b11);
	}
	str += len;
	return (ft_strjoin(result, ft_replace_vars(vars, str, qs), NULL, 0b11));
}
