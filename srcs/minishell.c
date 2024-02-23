/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:01:13 by ycontre           #+#    #+#             */
/*   Updated: 2024/02/23 13:37:26 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	DEBUG;
extern int	g_exit_code;

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

void	ft_exec_single_command(char *line, t_envvar **envp)
{
	t_token	*tokens;
	t_node	*tree;

	if (ft_to_tokens(&tokens, line, envp))
		return ;
	if (ft_to_tree(&tokens, &tree, envp))
	{
		ft_clear_tree(tree);
		exit(ERR_FAILED);
	}
	if (ft_heredoc_opening(tree))
		return ;
	ft_exec(tree, ft_init_executor(tree), EX_WAIT);
	ft_clear_tree(tree);
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*env;

	rl_catch_signals = 0;
	(void) argc;
	(void) argv;
	if (argc > 3)
		exit(ERR_FAILED);
	env = ft_setup_env(argv, envp);
	if (argc == 2 && !ft_strncmp(argv[1], "DEBUG", 6))
		DEBUG = 1;
	else if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		ft_exec_single_command(ft_strdup(argv[2]), &env);
		exit(g_exit_code);
	}
	else if (argc > 1)
	{
		ft_clear_env(env);
		exit(ERR_FAILED);
	}
	ft_print_logo(env);
	// rl_catch_signals = 0;
	ft_signal_state(SIGHANDLER_INT);
	while (1)
	{
		g_exit_code &= 0x00FFFFFF;
		ft_update_env(&env);
		ft_prompt_handler(&env);
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_envvar *env;
// 	(void) argc;
// 	env = ft_setup_env(argv, envp);
// 	ft_update_env(&env);
// 	int fd = ft_get_heredoc(ft_strdup("EOF"), ft_get_temp_file(".heredoc", 16));

// 	char buffer[4096];

// 	read(fd, buffer, 4096);

// 	printf("%s\n", buffer);

// 	close(fd);
// }