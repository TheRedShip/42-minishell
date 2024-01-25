/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:08:31 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 14:08:21 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envvar    *ft_setup_env(char **envp)
{
	t_envvar    *env;
	char		*tmp;
	int         i;

	i = -1;
	env = NULL;
	while (envp[++i])
		ft_add_var(&env, ft_init_var(envp[i]));
	if (ft_get_var(env, "SHLVL"))
		tmp = ft_itoa(1 + ft_atoi(ft_get_var(env, "SHLVL")->values[0]));
	ft_set_var(env, "SHLVL", tmp);
	free(tmp);
	return (env);
}


// int main(int argc, char **argv, char **envp)
// {
// 	t_envvar *environment;

// 	environment = ft_setup_env(envp);
// 	ft_remove_var(&environment, "LS_COLORS");
// 	ft_remove_var(&environment, "PATH");
// 	ft_remove_var(&environment, "USER");
// 	ft_remove_var(&environment, "SHELL");
// 	while (environment)
// 	{
// 		printf("Variable : %s\n", environment->name);
// 		int i = -1;
// 		while (environment->values[++i])
// 			printf("  valeur %d : %s\n", i, environment->values[i]);
// 		printf("\n");
// 		environment = environment->next;
// 	}
// 	return (0);
// }