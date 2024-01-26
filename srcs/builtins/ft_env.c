/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:05:11 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 07:52:25 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_var_size(t_envvar *vars)
{
    int size;

    size = 0;
    while (vars)
    {
        size++;
        vars = vars->next;
    }
    return (size);
}

char    *ft_get_varstring(t_envvar *var)
{
    char    *string;
    char    *tmp;
    int     i;

    i = 0;
    string = ft_strjoin(var->name, "=", 0);
    while (var->values[i])
    {
        tmp = string;
        if (!i)
            string = ft_strjoin(tmp, var->values[i], NULL);
        else
            string = ft_strjoin(tmp, var->values[i], ":");
        free(tmp);
        i++;
    }
    return (string);
}

int ft_env(t_command *cmd)
{
    t_envvar    *vars;
    char        **vars_array;
    int         size;
    int         i;

    vars = cmd->envp;
    size = ft_var_size(vars) + 1;
    vars_array = malloc(size * sizeof(char *));
    if (!vars_array)
        return (EC_FAILED);
    i = -1;
    while (++i < size - 1)
    {
        vars_array[i] = ft_get_varstring(vars);
        if (!vars_array[i])
        {
            ft_free_tab((void **)vars_array);
            return (EC_FAILED);
        }
        printf("%s\n", vars_array[i]);
        vars = vars->next;
    }
    vars_array[i] = 0;
    ft_free_tab((void **)vars_array);
    return (EC_SUCCES);
}
