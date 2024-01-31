/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:19:03 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/31 08:05:35 by rgramati         ###   ########.fr       */
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
	while (!ft_strchr(" $'\"", *str))
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

	printf("WORKING ON <%s>\n", str); //DEBUG ONLY
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
		while (!ft_strchr(" $'\"", *(str + len + 1)))
			len++;
		result = ft_strjoin(result, ft_strndup(str, ++len), NULL, 0b11);
	}
	str += len;
	return (ft_strjoin(result, ft_replace_vars(vars, str, qs), NULL, 0b11));
}

// int main(void)
// {
// 	char *string = "salut '$HOME' \"$HOME\" $?abcd salut$PATH";

// 	char *test = ft_replace_vars(NULL, string, QU_ZERO);
// 	printf("RESULT is <%s>\n", test);
// 	free(test);
// }
