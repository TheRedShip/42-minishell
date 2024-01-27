/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_envvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:33:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 14:14:02 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_add_var(t_envvar **vars, t_envvar *var)
{
	t_envvar	*tmp;

	if (!vars || !var)
		return ;
	if (!(*vars))
	{
		*vars = var;
		return ;
	}
	tmp = *vars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = var;
}

void	ft_remove_var(t_envvar **vars, char *name)
{
	t_envvar	*prv;
	t_envvar	*tmp;

	prv = NULL;
	tmp = *vars;
	while (tmp && ft_strcmp(tmp->name, name))
	{
		prv = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prv->next = tmp->next;
		ft_del_var(tmp);
	}
}

void	ft_del_var(t_envvar *var)
{
	char	**tmp;

	tmp = var->values;
	free(var->name);
	while (var->values && *(var->values))
	{
		free(*(var->values));
		var->values++;
	}
	free(tmp);
	free(var);
}

t_envvar	*ft_get_var(t_envvar *vars, char *name)
{
	while (vars && ft_strncmp(vars->name, name, ft_strlen(vars->name) + 1))
		vars = vars->next;
	return (vars);
}

t_envvar	*ft_last_var(t_envvar *vars)
{
	while (vars->next)
		vars = vars->next;
	return (vars);
}

void	ft_set_var(t_envvar *vars, char *name, char *nv)
{
	t_envvar	*head;

	head = vars;
	while (vars && ft_strncmp(vars->name, name, ft_strlen(name)))
		vars = vars->next;
	if (!vars)
	{
		ft_add_var(&head, ft_init_var(name));
		vars = ft_last_var(head);
	}
	ft_free_tab((void **)vars->values);
	vars->values = NULL;
	vars->values = ft_split(nv, ':');
}
