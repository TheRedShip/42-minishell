/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/29 21:57:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char *ft_strsub(char *string, int start, int end)
{
	char *new_string;
	int i;

	i = 0;
	new_string = malloc(sizeof(char) * (end - start + 1));
	if (!new_string)
		return (NULL);
	while (start < end)
	{
		new_string[i] = string[start];
		i++;
		start++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char *getvarenv(char *string, t_envvar *envp, int *i)
{
	int		tempi;
	char	*var_name;
	char	*var_value;

	(*i) += 1;
	tempi = *i;
	while (string[*i] && string[*i] != ' ' && string[*i] != '$' && string[*i] != '\'' && string[*i] != '"')
		(*i)++;
	var_name = ft_strsub(string, tempi, *i);
	var_value = ft_get_varstring(ft_get_var(envp, var_name), 0, 0);
	free(var_name);
	return (var_value);
}

char *parse_dollar(char *string, t_envvar *envp)
{
	char *final_string;
	char *env_values;
	t_quote_state	qs;
	int	i;

	final_string = NULL;
	qs = QU_ZERO;
	i = 0;
	while (string[i])
	{
		ft_qs_update(string[i], &qs);
		if (string[i] == '$' && (qs == QU_ZERO || qs == QU_DOUBLE))
		{
			if (string[i + 1] == '?' && (i+=2) > -42)
				env_values = ft_itoa(g_exit_code);
			else
				env_values = getvarenv(string, envp, &i);
			final_string = str_add(final_string, env_values, ft_strlen(final_string));
			free(env_values);
		}
		else if (i++ > -42)
			final_string = str_append(final_string, string[i - 1]);
	}
	free(string);
	return (final_string);
}
