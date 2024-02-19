/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/19 21:10:43 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnt_empty(char *str)
{
	char	*tmp;
	
	if (!*str)
		return (0);
	tmp = str;
	while (ft_isspace(*tmp))
		tmp++;
	return (*tmp);
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
	printf("\033[0m\n");
	close(fd);
}

char	*ft_get_temp_file(char *head, int size)
{
	int		urandom;
	char	*rand;
	char	*tmp;

	rand = ft_calloc((size + 1), sizeof(char));
	urandom = open("/dev/urandom", O_RDONLY);
	if (urandom < 0)
		return (NULL);
	read(urandom, rand, size);
	close(urandom);
	tmp = rand;
	while (size--)
	{
		while (!(ft_isalnum(*rand)))
			*rand = (unsigned char) *rand % 93 + 33;
		rand++;
	}
	return (ft_strjoin(head, tmp, "-", 0b10));
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*env;

	(void) argc;
	(void) argv;
	env = ft_setup_env(argv, envp);
	ft_print_logo(env);
	ft_signal_state(SIGHANDLER_INT);
	while (1)
	{
		ft_update_env(&env);
		ft_prompt_handle(&env);
	}
	return (0);
}
