/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/06 16:58:59 by rgramati         ###   ########.fr       */
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

void	ft_print_logo(t_envvar *envp)
{
	int		fd;
	char	*line;

	if (!ft_get_var(envp, "LOGOPWD"))
		return ;
	fd = open(ft_get_var(envp, "LOGOPWD")->values[0], 0);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	printf("\033c\033[31m");
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

char	*get_temp_file(char *head)
{
	int		urandom;
	char	rand[11];
	int		i;

	i = 0;
	rand[10] = 0;
	urandom = open("/dev/urandom", O_RDONLY);
	if (urandom < 0)
		return (NULL);
	read(urandom, rand, 10);
	close(urandom);
	while (i < 10)
	{
		while (!(ft_isalnum(rand[i])))
			rand[i] = (unsigned char) rand[i] % 93 + 33;
		i++;
	}
	return (ft_strjoin(head, rand, "-", 0b00));
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*env;

	(void) argc;
	(void) argv;
	env = ft_setup_env(argv, envp);
	ft_update_env(&env);
	ft_print_logo(env);
	while (1)
	{
		// toggle_signal(1);
		ft_prompt(&env);
	}
	return (0);
}
