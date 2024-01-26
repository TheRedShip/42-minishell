/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:46:06 by marvin            #+#    #+#             */
/*   Updated: 2024/01/18 17:46:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_only_ns(char *str)
{
	str++;
	while (*(str) == 'n')
		str++;
	printf("il reste [%s]\n", str);
	return (!*str);
}

// int ft_echo(t_command *cmd)
// {
// 	int		i;
// 	int		trailing;
// 	char	*string;
// 	char	*tmp;

// 	i = 1;
// 	trailing = 1;
// 	if (cmd->args[i])
// 		trailing = !(!ft_strncmp(cmd->args[i], "-n", 2) && ft_only_ns(cmd->args[i]));
// 	i += !trailing;
// 	string = NULL;
// 	while (i < ft_tab_len(cmd->args))
// 	{
// 		tmp = string;
// 		if (i != 1 + !trailing)
// 			string = ft_strjoin(tmp, cmd->args[i++], " ");
// 		else
// 			string = ft_strjoin(tmp, cmd->args[i++], NULL);
// 		free(tmp);
// 	}
// 	if (string)
// 		printf("%s", string);
// 	if (trailing)
// 		printf("\n");
// 	free(string);
// 	return (EC_SUCCES);
// }

int	ft_echo(t_command *cmd)
{
	for(int i = 0; i < ft_tab_len(cmd->args); i++)
		printf("|%s|\n", cmd->args[i]);
	return (0);
}