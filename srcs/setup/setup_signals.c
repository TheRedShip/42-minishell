/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:42:59 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 23:42:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   ft_sigint(int sig)
{
	(void)sig;
	printf("\nminishell>");
}

void   ft_sigquit(int sig)
{
	(void)sig;
	printf("\b\b");
}

void	ft_setup_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
}