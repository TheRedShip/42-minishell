/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:52:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/27 08:35:46 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_open_dquote(t_quote_state qs)
{
	char	*line;
	char	*prompt;

	if (qs == QU_SINGLE)
	{
		prompt = ft_strjoin(P_SDQUOTE, P_ENDQUOTE, NULL, 0);
		line = readline(prompt);
	}
	if (qs == QU_DOUBLE)
	{
		prompt = ft_strjoin(P_DDQUOTE, P_ENDQUOTE, NULL, 0);
		line = readline(prompt);
	}
	free(prompt);
	return (line);
}
