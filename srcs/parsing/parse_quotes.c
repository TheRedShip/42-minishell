/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:53:31 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/26 16:13:42 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	change_quote_state(int *quote_state, char *string, int *i)
{
	if (string[*i] == '"' && *quote_state == 0)
	{
		(*i)++;
		*quote_state = 1;
	}
	else if (string[*i] == '"' && *quote_state == 1)
	{
		(*i)++;
		*quote_state = 0;
		change_quote_state(quote_state, string, i);
	}
	else if (string[*i] == '\'' && *quote_state == 0)
	{
		(*i)++;
		*quote_state = 2;
	}
	else if (string[*i] == '\'' && *quote_state == 2)
	{
		(*i)++;
		*quote_state = 0;
		change_quote_state(quote_state, string, i);
	}
}

char	*parse_quotes(char *string)
{
	int		i;
	int		j;
	int 	quote_status;
	char	*final_string;

	i = -1;
	j = 0;
	quote_status = 0;
	final_string = NULL;
	while (i < (int)(ft_strlen(string)) && string[++i])
	{
		change_quote_state(&quote_status, string, &i);
		while (string[i] == '"' && quote_status == 1)
			change_quote_state(&quote_status, string, &i);
		while (string[i] == '\'' && quote_status == 2)
			change_quote_state(&quote_status, string, &i);
		final_string = str_append(final_string, string[i]);
	}
	free(string);
	return (final_string);	
}
