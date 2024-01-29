/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:34 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/29 22:04:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token(char *str, t_quote_state qs)
{
	if (!ft_strncmp(str, "\"", 1) && (qs == QU_DOUBLE))
		return (1);
	if (!ft_strncmp(str, "'", 1) && (qs == QU_SINGLE))
		return (1);
	if (!ft_strncmp(str, " ", 1) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, "(", 1) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, ")", 1) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, "||", 2) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, "&&", 2) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, "|", 1) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, ">>", 2) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, ">", 1) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, "<<", 2) && (qs == QU_ZERO))
		return (1);
	if (!ft_strncmp(str, "<", 1) && (qs == QU_ZERO))
		return (1);
	return (0);
}
