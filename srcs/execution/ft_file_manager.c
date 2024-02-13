/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:02:28 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/12 21:01:07 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_manage_file(t_token **tokens, int **fds)
// {
// 	int		state;

// 	state = !ft_strncmp((*tokens)->str, "<", 2) + 2 * !ft_strncmp((*tokens)->str, "<<", 3);
// 	printf("TESTING: state = [%d]\n", state);
// 	if (state)
// 	{
// 		printf("DEBUG :  OPENING INFILE: current = [%d], state = [%d]\n", (*fds)[0], state);
// 		if ((*fds)[0] > 2)
// 		{
// 			// printf("I CLOSE [%d]\n", (*fds)[0]);
// 			close((*fds)[0]);
// 		}
// 		if (state & 0b01)
// 			(*fds)[0] = open(((*tokens)->next)->str, OPEN_READ);
// 		else if (state & 0b10 && (*fds)[2] < 16)
// 		{
// 			(*fds)[0] = ft_get_heredoc(((*tokens)->next)->str);
// 			(*fds)[2]++;
// 		}
// 		else
// 			return (EC_FAILED);
// 		printf("FILE OPENED: fd = [%d]\n", (*fds)[0]);
// 	}
// 	state = !ft_strncmp((*tokens)->str, ">", 2) + 2 * !ft_strncmp((*tokens)->str, ">>", 3);
// 	// printf("TESTING: state = [%d]\n", state);
// 	if (state)
// 	{
// 		printf("DEBUG : OPENING OUTFILE: current = [%d], state = [%d]\n", (*fds)[1], state);
// 		if ((*fds)[1] > 2)
// 		{
// 			// printf("I CLOSE [%d]\n", (*fds)[1]);
// 			close((*fds)[1]);
// 		}
// 		if (state & 0b01)
// 			(*fds)[1] = open(((*tokens)->next)->str, OPEN_CREATE, 0644);
// 		else if (state & 0b10)
// 			(*fds)[1] = open(((*tokens)->next)->str, OPEN_APPEND, 0644);
// 		printf("FILE OPENED: fd = [%d]\n", (*fds)[1]);
// 	}
// 	(*tokens) = (*tokens)->next;
// 	return (EC_SUCCES);
// }

int	ft_get_heredoc(char *delim)
{
	(void) delim;
	return (10);
}

int	ft_manage_inputs(t_token **tokens, int *fd, int *hd)
{
	int		state;

	state = !ft_strncmp((*tokens)->str, "<", 2) + 2 * !ft_strncmp((*tokens)->str, "<<", 3);
	if (state)
	{
		if (*fd > 2)
			close(*fd);
		if (state & 0b01)
			*fd = open(((*tokens)->next)->str, OPEN_READ);
		else if (state & 0b10 && *hd < 16)
		{
			*fd = ft_get_heredoc(((*tokens)->next)->str);
			(*hd)++;
		}
		else
			return (EC_FAILED);
		(*tokens) = (*tokens)->next;
	}
	return (EC_SUCCES);
}

int	ft_manage_outputs(t_token **tokens, int *fd)
{
	int		state;

	state = !ft_strncmp((*tokens)->str, ">", 2) + 2 * !ft_strncmp((*tokens)->str, ">>", 3);
	if (state)
	{
		if (*fd > 2)
			close(*fd);
		if (state & 0b01)
			*fd = open(((*tokens)->next)->str, OPEN_CREATE, 0644);
		else if (state & 0b10)
			*fd = open(((*tokens)->next)->str, OPEN_APPEND, 0644);
		(*tokens) = (*tokens)->next;
	}
	return (EC_FAILED);
}

void	ft_close_command(t_node *tree)
{
	if (tree->command)
	{
		if (tree->command->infile > 2)
			close(tree->command->infile);
		if (tree->command->outfile > 2)
			close(tree->command->outfile);
	}
}

void	ft_close_tree_rec(t_node *tree)
{
	if (tree->left)
		ft_close_tree_rec(tree->left);
	if (tree->right)
		ft_close_tree_rec(tree->right);
	ft_close_command(tree);
}

void	ft_close_files(t_node *root, t_executor *ex)
{
	ft_close_tree_rec(root);
	if (ex->input > 2)
		close(ex->input);
	if (ex->output > 2)
		close(ex->output);
	if (ex->pipes)
	{
		close(ex->pipes->fd[0]);
		close(ex->pipes->fd[1]);
	}
}
