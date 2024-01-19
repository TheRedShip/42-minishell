/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:53:31 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/19 16:57:19 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *get_env_var(char *string)
{
	int	i;
	int	j;
	char *env_var;

	i = 0;
	j = 0;
	while (string[i] && string[i] != ' ' && string[i] != '\t' && string[i] != '\n' && string[i] != '\"' && string[i] != '$')
		i++;
	env_var = (char *)malloc(sizeof(char) * (i + 1));
	if (!env_var)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != ' ' && string[i] != '\t' && string[i] != '\n' && string[i] != '\"' && string[i] != '$')
	{
		env_var[j] = string[i];
		i++;
		j++;
	}
	env_var[j] = '\0';
	return (env_var);
}

void	change_quote_state(int *quote_state, char *string, int i)
{
	if (string[i] == '"' && *quote_state == 0)
		*quote_state = 1;
	else if (string[i] == '"' && *quote_state == 1)
		*quote_state = 0;
	else if (string[i] == '\'' && *quote_state == 0)
		*quote_state = 2;
	else if (string[i] == '\'' && *quote_state == 2)
		*quote_state = 0;
}

int calcul_len_string(char *string)
{
	int	i;
	int	string_size;
	int	quote_state;
	char *temp_string;
	
	string_size = 0;
	quote_state = 0;
	i = 0;
	while (string[i])
	{
		change_quote_state(&quote_state, string, i);
		if ((quote_state == 1 || quote_state == 0) && string[i] == '$' && (string[i + 1] != '$' && string[i + 1] != '\0'))
		{
			temp_string = get_env_var(&string[i + 1]);
			if (!temp_string)
				return (-1);
			string_size += ft_strlen(getenv(temp_string));
			i += ft_strlen(temp_string);
			free(temp_string);
		}
		else
			string_size++;		
		i++;
	}
	return (string_size);
}

int create_new_string(char *string, char *new_string)
{
	
}

char	*parse_quotes(char *string)
{
	int	final_len;
	char *new_string;
	
	final_len = calcul_len_string(string);
	if (final_len == -1)
		return (NULL);
	new_string = (char *)ft_calloc(sizeof(char), (final_len + 1));
	if (!new_string)
		return (NULL);
	new_string[final_len] = '\0';
	printf("%d\n", final_len);
	if (create_new_string(string, new_string) == -1)
		return (NULL);
	return (new_string);
}
