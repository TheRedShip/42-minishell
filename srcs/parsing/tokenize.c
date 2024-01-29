/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:55:34 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/29 16:52:12 by ycontre          ###   ########.fr       */
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