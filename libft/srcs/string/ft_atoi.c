/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:38:15 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/04 13:30:20 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	sign;
	int	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (*(nptr + i) == 32 || (*(nptr + i) >= 9 && *(nptr + i) <= 13))
		i++;
	if (*(nptr + i) == 43 || *(nptr + i) == 45)
	{
		if (*(nptr + i) == 45)
			sign = -1;
		i++;
	}
	while (*(nptr + i) >= 48 && *(nptr + i) <= 57)
	{
		sum *= 10;
		sum += (*(nptr + i) - 48);
		i++;
	}
	return (sign * sum);
}

int	ft_atoi(char *nptr)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = (int) 2 * (0.5 - (*(nptr++) == '-'));
	while (ft_isdigit(*nptr))
		n = n * 10 + (int){*(nptr++) - '0'};
	return (sign * n);
}
