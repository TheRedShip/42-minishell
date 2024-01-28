/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:08:31 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/28 18:51:59 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_env(t_envvar **env)
{
	(void) env;
	return ;
}

t_envvar    *ft_setup_env(char **envp)
{
	t_envvar    *env;
	char		*tmp;
	int         i;

	i = -1;
	env = NULL;
	tmp = NULL;
	while (envp[++i])
		ft_add_var(&env, ft_init_var(envp[i]));
	if (ft_get_var(env, "SHLVL"))
		tmp = ft_itoa(1 + ft_atoi(ft_get_var(env, "SHLVL")->values[0]));
	else
		tmp = ft_strdup("1");
	ft_set_var(&env, "SHLVL", tmp);
	tmp = ft_strdup("minishell");
	ft_set_var(&env, "SHELL", tmp);
	return (env);
}
