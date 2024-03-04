/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:59:54 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/04 23:36:35 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipes	*ft_init_pipes(void)
{
	t_pipes	*new_pipe;

	new_pipe = malloc(sizeof(t_pipes));
	if (!new_pipe)
		return (NULL);
	new_pipe->fd[0] = -1;
	new_pipe->fd[1] = -1;
	if (pipe(new_pipe->fd) == -1)
	{
		free(new_pipe);
		return (NULL);
	}
	new_pipe->next = NULL;
	return (new_pipe);
}

void	ft_pipes_push(t_pipes **head, t_pipes *top)
{
	if (!head || !top)
		return ;
	if (!*head)
	{
		*head = top;
		return ;
	}
	top->next = *head;
	*head = top;
}

t_pipes	*ft_pipes_pop(t_pipes **head)
{
	t_pipes	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	tmp->next = NULL;
	return (tmp);
}

void	ft_del_pipe(t_pipes *p)
{
	if (p->fd[0] > 2)
		close(p->fd[0]);
	if (p->fd[1] > 2)
		close(p->fd[1]);
	free(p);
}
