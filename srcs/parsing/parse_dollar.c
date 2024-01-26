/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/26 14:03:31 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_envvar *getvarenv(char *string, t_envvar *envp)
{
	int i;
	char *var_name;
	t_envvar *var_value;

	i = 0;
	while (string[i] && string[i] != ' ' && string[i] != '$')
		i++;
	var_name = ft_strsub(string, 0, i);
	var_value = ft_get_var(envp, var_name);
	free(var_name);
	return (var_value);
}

char *parse_dollar(char *string, t_envvar *envp)
{
	char *final_string;
	char **env_values;
	t_quote_state	qs;
	int	i;
	int	j;

	final_string = NULL;
	qs = QU_ZERO;
	i = 0;
	while (string[i])
	{
		ft_qs_update(string[i], &qs);
		if (string[i] == '$' && (qs == QU_ZERO || qs == QU_DOUBLE))
		{
			env_values = getvarenv(string + i + 1, envp)->values;
			j = 0;
			while (env_values[j])
			{
				final_string = str_add(final_string, env_values[j], ft_strlen(final_string));
				final_string = str_append(final_string, ':');
				i += ft_strlen(env_values[j]) + 1;
				j++;
			}
		}
		else
		{
			final_string = str_append(final_string, string[i]);
			i++;
		}
	}
	return (final_string);
}