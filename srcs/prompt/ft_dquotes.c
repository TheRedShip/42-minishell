/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:52:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/26 16:14:18 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_open_dquote(t_quote_state qs)
{
	char	*line;

	if (qs == QU_SINGLE)
		line = readline(P_SDQUOTE);
	if (qs == QU_DOUBLE)
		line = readline(P_DDQUOTE);
	return (line);
}
