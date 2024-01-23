/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:08:31 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/23 17:59:44 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envvar    *ft_new_var(char *value)
{
	t_envvar    *new_var;
	char        *name;

	new_var = malloc(sizeof(t_envvar));
	name = ft_strdup(ft_strtok(value, "="));
	new_var->name = name;
	new_var->values = ft_split(value + ft_strlen(name) + 1, ':');
	new_var->next = NULL;
	return (new_var);
}

void    ft_add_var(t_envvar **vars, t_envvar *new_var)
{
	t_envvar	*tmp;

	if (!vars || !new_var)
		return ;
	if (!(*vars))
	{
		*vars = new_var;
		return ;
	}
	tmp = *vars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_var;
}

t_envvar    *ft_setup_env(char **envp)
{
	t_envvar    *env;
	int         i;

	i = -1;
	env = NULL;
	while (envp[++i])
		ft_add_var(&env, ft_new_var(envp[i]));
	return (env);
}

void	ft_del_var(t_envvar *var)
{
	char	**tmp;

	tmp = var->values;
	free(var->name);
	while (*(var->values))
	{
		free(*(var->values));
		var->values++;
	}
	free(tmp);
}

void	ft_remove_var(t_envvar **env, char *name)
{
	t_envvar	*prv;
	t_envvar	*tmp;

	prv = NULL;
	tmp = *env;
	while (ft_strcmp(tmp->name, name))
	{
		prv = tmp;
		tmp = tmp->next;
	}
	prv->next = tmp->next;
	ft_del_var(tmp);
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