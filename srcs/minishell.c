/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/01/31 07:51:36 by rgramati         ###   ########.fr       */
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
	int 		debugging;
	char		*debug_file;

	(void) argc;
	(void) argv;
	debugging = -1;
	if (argc == 2 && !ft_strncmp(argv[1], "debug", 6))
	{
		debug_file = ft_strjoin("./.logs/", get_temp_file(".debug"), NULL, 0b10);
		debugging = open(debug_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(debugging, STDOUT_FILENO);
		// ft_debug_adress(debug_file, debugging);
	}
	toggle_signal(1);
	env = ft_setup_env(argv, envp);
	ft_update_env(&env);
	ft_print_logo();
	while (1)
		ft_prompt(&env);
	return (0);
}
