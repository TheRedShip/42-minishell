/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/25 16:35:38 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **str_copy(char **string)
{
	char **new_string;
	int i;

	i = 0;
	while (string[i])
		i++;
	new_string = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (string[i])
	{
		new_string[i] = ft_strdup(string[i]);
		i++;
	}
	new_string[i] = NULL;
	return (new_string);
}

int main(int argc, char **argv, char **envp)
{
	char **env_copy;
	t_envvar	*env;
	(void) argc;
	(void) argv;

	toggle_signal(1);
	env_copy = str_copy(envp);
	env = ft_setup_env(env_copy);
	while (1)
		ft_prompt(env, envp);
	// ft_free_tab(env_copy);
	return (0);
}