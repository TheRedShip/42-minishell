/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:06:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/29 13:29:40 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_strs(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_strs_tab(char **tab, int size)
{
	int	min;
	int	curr;
	int	swp;
	int	len;

	curr = 0;
	while (curr <= size)
	{
		min = curr;
		swp = curr + 1;
		while (swp <= size - 1)
		{
			len = ft_strlen(*(tab + swp)) + 1;
			if (ft_strncmp(*(tab + swp), *(tab + min), len) < 0)
				min = swp;
			swp++;
		}
		ft_swap_strs(tab + curr, tab + min);
		curr++;
	}
}

int	ft_show_export_list(t_command *cmd)
{
	char	**vars_array;
	char	**tmp;
	char	*string;

	vars_array = ft_get_var_strs(cmd->envp, 1);
	if (!vars_array)
		return (EC_FAILED);
	ft_sort_strs_tab(vars_array, ft_tab_len(vars_array));
	tmp = vars_array;
	while (*tmp)
	{
		if (**tmp != '_')
		{
			string = ft_strjoin("declare -x ", *tmp, NULL, 0);
			printf("%s\n", string);
			free(string);
		}
		tmp++;
	}
	ft_free_tab((void **)vars_array);
	return (EC_SUCCES);
}

int	ft_str_unquoted_len(char *str)
{
	char	*tmp;
	int		i;

	tmp = str;
	while (*str)
	{
		i += ((*str) == '"') + ((*str) == '\'');
		str++;
	}
	return (str - tmp - i);
}

int	ft_export_var(t_command *cmd)
{
	char	**tmp;
	char	**tmp2;

	tmp = cmd->args;
	while (*(++tmp))
	{
		printf("DEBUG > %s\n", *tmp);
		if (ft_strchr(*tmp, '='))
		{
			tmp2 = ft_split(*tmp, '=');
			if (tmp2[1])
				ft_set_var(&(cmd->envp), tmp2[0], ft_strtrim(tmp2[1], "\"'"));
			else
				ft_set_var(&(cmd->envp), tmp2[0], "");
			ft_free_tab((void **)tmp2);
		}
		else
			ft_set_var(&(cmd->envp), *tmp, NULL);
	}
	return (EC_SUCCES);
}

int	ft_export(t_command *cmd)
{
	if (ft_tab_len(cmd->args) == 1)
	{
		if (ft_show_export_list(cmd))
			return (EC_FAILED);
	}
	else
	{
		if (ft_export_var(cmd))
			return (EC_FAILED);
	}
	return (EC_SUCCES);
}
