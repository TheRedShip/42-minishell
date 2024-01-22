/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:08:31 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/22 11:25:32 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envvar    *ft_newvar(char *value)
{
    t_envvar    *new_var;
    char        **data;
    char        *name;

    new_var = malloc(sizeof(t_envvar));
    data = ft_split(value, "=");
    name = ft_strdup(data[0]);
    ft_free_tab(data);
    new_var->name = name;
    new_var->values = ft_split(value + ft_strlen(name) + 1, ":");
    new_var->next = NULL;
    return (new_var);
}

t_envvar    *ft_addvar(t_envvar **vars, t_envvar *new_var)
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
    t_ennvar    *env;
    int         i;

    i = 0;
    while (envp[i])
        ft_addvar(&env, ft_newvar(envp[i]));
    return (env);
}