/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_envvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:33:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/19 17:10:14 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_var(t_envvar **vars, t_envvar *var)
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
	t_envvar	*head;

	tmp = *vars;
	prv = tmp;
	head = NULL;
	while (tmp && ft_strcmp(tmp->name, name))
	{
		prv = tmp;
		tmp = tmp->next;
	}
	if (prv == tmp)
		head = tmp->next;
	if (tmp && prv)
	{
		prv->next = tmp->next;
		ft_del_var(tmp);
	}
	if (head)
		*vars = head;
}

void	ft_del_var(t_envvar *var)
{
	free(var->name);
	if (var->values && *(var->values))
		ft_free_tab((void **) var->values);
	else
		free(var->values);
	free(var);
}

void	ft_clear_env(t_envvar *vars)
{
	t_envvar	*tmp;

	while (vars)
	{
		tmp = vars->next;
		ft_del_var(vars);
		vars = tmp;
	}
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

void	ft_set_var(t_envvar **vars, char *name, char *string)
{
	t_envvar	*head;

	head = *(vars);
	while (*(vars) && ft_strncmp((*vars)->name, name, ft_strlen(name)))
		*(vars) = (*vars)->next;
	if (!*(vars))
	{
		ft_add_var(&head, ft_init_var(name));
		*(vars) = ft_last_var(head);
	}
	ft_free_tab((void **)(*vars)->values);
	(*vars)->values = NULL;
	(*vars)->values = ft_split(string, ':');
	*(vars) = head;
	if (ft_strlen(string))
		free(string);
}

void	ft_append_var(t_envvar **vars, char *name, char *string)
{
	t_envvar	*head;
	char		*tmp;

	head = *(vars);
	name[ft_strlen(name) - 1] = 0;
	while (*(vars) && ft_strncmp((*vars)->name, name, ft_strlen(name)))
		*(vars) = (*vars)->next;
	tmp = ft_get_varstring(*vars, 0, 0);
	tmp = ft_strjoin(tmp, string, NULL, 0b11);
	ft_set_var(&head, name, tmp);
	*(vars) = head;
}
