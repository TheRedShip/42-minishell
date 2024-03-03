/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_envar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:02:48 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 16:03:56 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
