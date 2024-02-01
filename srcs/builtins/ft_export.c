/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:06:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/01 13:47:43 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_export_syntaxer(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_isdigit(str[0]))
// 		return (0);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '"' && str[i] != '\'')
// 			return (0);
// 		i++;
// 	}
// 	if (i == 0)
// 		return (0);
// 	return (1);
// }

int	ft_export_syntaxer(char *str)
{
	char	*tmp;

	tmp = str;
	if (ft_isdigit(*str) || !*str)
		return (0);
	while (*str && (ft_isalnum(*str) || *str == '\'' || *str == '"') && *str != '=')
		str++;
	if (*str == '+' && *(str + 1) == '=')
		return (1);
	return (tmp != str);
}

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

	vars_array = ft_get_var_strs(*(cmd->envp), 1);
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

int	ft_export_var(t_command *cmd, char *tmp)
{
	char	**var;
	
	if (ft_strchr(tmp, '='))
	{
		var = ft_split(tmp, '=');
		if (ft_strlen(var[0]) && var[0][ft_strlen(var[0]) - 1] == '+')
			ft_append_var(cmd->envp, var[0], ft_strtrim(var[1], "\"'"));
		else
		{
			if (var[1])
				ft_set_var(cmd->envp, var[0], ft_strtrim(var[1], "\"'"));
			else
				ft_set_var(cmd->envp, var[0], "");
		}
		ft_free_tab((void **)var);
	}
	else
		ft_set_var(cmd->envp, tmp, NULL);
	return (EC_SUCCES);
}

int	ft_export(t_command *cmd)
{
	char	**tmp;

	tmp = cmd->args;
	if (ft_tab_len(tmp) == 1)
	{
		if (ft_show_export_list(cmd))
			return (EC_FAILED);
	}
	else
	{
		while (*(++tmp))
		{
			if (!ft_export_syntaxer(*tmp))
			{
				printf("minishell: export: `%s': not a valid identifier\n", *tmp);
				return (EC_FAILED);
			}
			if (ft_export_var(cmd, *(tmp)))
				return (EC_FAILED);
		}
	}
	return (EC_SUCCES);
}
