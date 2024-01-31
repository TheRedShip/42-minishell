/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:55:37 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/31 10:19:48 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(void **tab)
{
	void	**tmp;

	if (!tab)
		return ;
	tmp = tab;
	while (*tmp)
		free(*(tmp++));
	free(tab);
}
