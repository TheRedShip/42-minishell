/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:06:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 10:09:12 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_sort_strs_tab(int *tab, int size)
// {
// 	int	min;
// 	int	current;
// 	int	swp;

// 	current = 0;
// 	while (current <= size)
// 	{
// 		min = current;
// 		swp = current + 1;
// 		while (swp <= size - 1)
// 		{
// 			if (tab[swp] < tab[min])
// 				min = swp;
// 			swp++;
// 		}
// 		ft_swap(&tab[current], &tab[min]);
// 		current++;
// 	}
// }

int ft_export(t_command *cmd)
{
    (void) cmd;
    return (EC_SUCCES);
    // t_envvar    *vars;
    // char        **vars_array;
    // char        **args;
    // int         size;

    // vars = cmd->envp;
    // size = ft_var_size(vars) + 1;
    // if (ft_tab_len(cmd->args))
    //     args = ft_split(cmd->args[1], '=');
    // else
    // {
    //    return (EC_FAILED);
    // }
    // return (EC_SUCCES);
}
