/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/30 12:48:07 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**str_copy(char **string)
{
	char	**new_string;
	int		i;

	i = 0;
	while (string[i])
		i++;
	new_string = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (string[i])
	{
		new_string[i] = ft_strdup(string[i]);
		i++;
	}
	new_string[i] = NULL;
	return (new_string);
}

void	ft_print_logo(void)
{
	int		fd;
	char	*line;

	fd = open("logosang", O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	printf("\033[2J\033[H\033[31m");
	while (line)
	{
		usleep(20000);
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\033[0m");
	printf("\033[37;1;3mby rgramati, ycontre\033[0m\n\n");
	close(fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*env;

	(void) argc;
	(void) argv;
	toggle_signal(1);
	env = ft_setup_env(argv, envp);
	ft_update_env(env);
	ft_print_logo();
	while (1)
		ft_prompt(env);
	return (0);
}
