/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:06:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 12:10:46 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_swap_strs(char **a, char **b)
{
    char    *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void	ft_sort_strs_tab(char **tab, int size)
{
	int min;
	int	curr;
	int	swp;

	curr = 0;
	while (curr <= size)
	{
		min = curr;
		swp = curr + 1;
		while (swp <= size - 1)
		{
			if (ft_strncmp(*(tab + swp), *(tab + min), 1) < 0)
				min = swp;
			swp++;
		}
		ft_swap_strs(tab + curr, tab + min);
		curr++;
	}
}

int ft_show_export_list(t_command *cmd)
{
    char    **vars_array;
    char    **tmp;
    char    *string;

    vars_array = ft_get_var_strs(cmd->envp, 1);
    if (!vars_array)
        return (EC_FAILED);
    ft_sort_strs_tab(vars_array, ft_tab_len(vars_array));
    tmp = vars_array;
    while (*tmp)
    {
        string = ft_strjoin("declare -x ", *tmp, NULL, 0);
        printf("%s\n", string);
        free(string);
        tmp++;
    }
    ft_free_tab((void **)vars_array);
    return (EC_SUCCES);
}

int ft_export(t_command *cmd)
{
    char    **tmp;

    if (ft_tab_len(cmd->args) == 1)
    {
        if (ft_show_export_list(cmd))
            return (EC_FAILED);
    }
    else
    {
        tmp = cmd->args;
        while (*tmp)
        {
            ft_set_var(cmd->envp, *tmp, "");
            tmp++;
        }
    }
    return (EC_SUCCES);
}
