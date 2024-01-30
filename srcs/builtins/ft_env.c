/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:05:11 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/30 14:38:44 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_var_size(t_envvar *vars)
{
	int	size;

	size = 0;
	while (vars)
	{
		size++;
		vars = vars->next;
	}
	return (size);
}

char	*ft_get_varstring(t_envvar *var, int format, int named)
{
	char	*string;
	int		i;

	string = NULL;
	if (var == NULL)
		return (NULL);
	i = 0;
	if (!var->values)
		return (ft_strdup(var->name));
	if (named)
		string = ft_strjoin(ft_strdup(var->name), "=", NULL, 0b01);
	if (format)
		string = ft_strjoin(string, "\"", NULL, 1);
	while (var->values[i])
	{
		if (!i)
			string = ft_strjoin(string, var->values[i++], NULL, 0b01);
		else
			string = ft_strjoin(string, var->values[i++], ":", 0b01);
	}
	if (format)
		string = ft_strjoin(string, "\"", NULL, 0b01);
	return (string);
}

char	**ft_get_var_strs(t_envvar *vars, int format)
{
	int		i;
	char	**vars_array;
	int		size;

	i = -1;
	size = ft_var_size(vars) + 1;
	vars_array = malloc(size * sizeof(char *));
	if (!vars_array)
		return (NULL);
	while (++i < size - 1)
	{
		vars_array[i] = ft_get_varstring(vars, format, 1);
		if (!vars_array[i])
		{
			ft_free_tab((void **)vars_array);
			return (NULL);
		}
		vars = vars->next;
	}
	vars_array[i] = NULL;
	return (vars_array);
}

int	ft_env(t_command *cmd)
{
	t_envvar	*vars;
	char		**vars_array;
	char		**tmp;

	vars = *(cmd->envp);
	vars_array = ft_get_var_strs(vars, 0);
	if (!vars_array)
		return (EC_FAILED);
	tmp = vars_array;
	while (*tmp)
	{
		if (ft_strchr(*tmp, '='))
			printf("%s\n", *tmp);
		tmp++;
	}
	ft_free_tab((void **)vars_array);
	return (EC_SUCCES);
}
