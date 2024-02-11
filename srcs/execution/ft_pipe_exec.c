/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/11 20:50:58 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_process_redirs(t_command *cmd, t_executor *ex)
// {
// 	(void) cmd;
// 	(void) ex;
// }

// void	ft_exec(t_node *cmd_tree, t_executor *ex)
// {
// 	t_node		*tmp;
// 	pid_t		pid[1024];
// 	static int	current = 0;

// 	tmp = cmd_tree;
// 	if (!tmp)
// 		return ;
// 	while (tmp)
// 	{
// 		if (tmp->token && (tmp->token->type & TK_PIPEXS))
// 			ft_pipe_exec(tmp, NULL);
// 		if (tmp->command)
// 			pid[current++] = ft_command_exec(tmp, ex->input, ex->output);
// 	}
// }

// void	ft_pipe_exec(t_node *cmd_tree, t_executor *ex)
// {
// 	ft_exec(cmd_tree->left, ex);
// 	ft_exec(cmd_tree->right, ex);
// }

// pid_t	ft_command_exec(t_node *cmd_tree, t_executor *ex)
// {
// 	pid_t	pid;

// 	pipe(ex->pipe_fd);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		ft_process_redirs(cmd_tree->command, ex);
// 		printf("je suis le fils\n");
// 		exit(EC_SUCCES);
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*command = NULL;
// 	t_envvar	*environment = ft_setup_env(argv, envp);
// 	t_token		*token_list;
// 	int			fd_command = open("../../commands.tst", O_RDONLY);
// 	char		**test_commands;
// 	char		*line;

// 	(void) argc;
// 	printf("%d\n", fd_command);
// 	while ((line = get_next_line(fd_command)))
// 		command = ft_strjoin(command, line, NULL, 0b01);
// 	close(fd_command);

// 	test_commands = ft_split(command, '\n');
// 	free(command);

// 	while (1)
// 	{
// 		command = readline("num ?: ");
// 		if (!command)
// 			continue ;
// 		int cmd_num = ft_atoi_base(command, 16);
// 		if (!cmd_num)
// 		{
// 			if (command)
// 				free(command);
// 			ft_clear_env(environment);
// 			exit(EXIT_FAILURE);
// 		}

// 		token_list = ft_tokenizer(command, QU_ZERO);
// 		ft_format_tokens(&token_list);
// 		ft_remove_braces(&token_list);
// 		t_token *t;
// 		t = token_list;
// 		printf("------------- ACTUAL TOKEN LIST -------------\n");
// 		while (t)
// 		{
// 			printf("%s ", t->str);
// 			t = t->next;
// 		}
// 		printf("\n---------------------------------------------\n");
// 		t_node *tree = ft_build_tree(token_list, &environment);
// 		treeprint(tree, 0);
// 		ft_clear_token_list(token_list);
// 		ft_clear_tree(tree);
// 		free(command);
// 	}
// 	ft_clear_env(environment);
// }
