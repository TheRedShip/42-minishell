/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:06:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/17 14:17:28 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_syntaxer(char *str)
{
	char	*tmp;

	tmp = str;
	if (ft_isdigit(*str) || !*str)
		return (0);
	while (*str && (ft_isalnum(*str) || *str == '_') && *str != '=')
		str++;
	if (*str == '+' && *(str + 1) == '=')
		return (1);
	return ((tmp != str && *str == '=') || !*str);
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
		if (ft_strncmp(*tmp, "_=", 2))
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

	var =NULL;
	if (ft_strchr(tmp, '='))
	{
		ft_strapp(&var, ft_strndup(tmp, ft_strcspn(tmp, "=")));
		ft_strapp(&var, ft_strdup(tmp + ft_strlen(*var) + 1));
		if (ft_strlen(var[0]) && var[0][ft_strlen(var[0]) - 1] == '+')
			ft_append_var(cmd->envp, var[0], ft_strtrim(var[1], "\""));
		else
		{
			if (var[1])
				ft_set_var(cmd->envp, var[0], ft_strtrim(var[1], "\""));
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
	char			**tmp;
	t_error_code	errcode;
	static	char 	err[] = "%sexport: `%s': not a valid identifier\n";

	tmp = cmd->args;
	ft_display_command(cmd);
	errcode = EC_SUCCES;
	if (ft_tab_len(tmp) == 1 && ft_show_export_list(cmd))
		errcode = EC_FAILED;
	else
	{
		while (*(++tmp))
		{
			if (!ft_export_syntaxer(*tmp))
			{
				printf(err, MINI, *tmp);
				errcode = EC_FAILED;
			}
			if (ft_export_var(cmd, *(tmp)))
				errcode = EC_FAILED;
		}
	}
	return (errcode);
}
