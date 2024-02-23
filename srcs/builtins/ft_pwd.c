/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:35:12 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/20 15:35:12 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*ft_trim_pwd(char *str)
{
	char	*lastb;

	lastb = ft_strrchr(str, '/');
	if (!lastb)
		return (ft_strdup(""));
	return (ft_strdup(lastb));
}

char	*ft_get_pwd(void)
{
	char	cwd[65536];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}

int	ft_pwd(t_command *cmd)
{
	char	cwd[65536];

	(void) cmd;
	if (getcwd(cwd, sizeof(cwd)))
		ft_dprintf(cmd->outfile, "%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (ERR_FAILED);
	}
	return (ERR_NOERRS);
}

char	*ft_get_prompt_string(t_envvar *envp)
{
	static t_envvar		*save = NULL;
	char				*prompt;
	char				*pwd;

	if (envp)
		save = envp;
	if (ft_get_var(save, "PWD"))
	{
		pwd = ft_trim_pwd(ft_get_var(save, "PWD")->values[0]);
		pwd = ft_strjoin(pwd, " ~ ", 0, 0b01);
	}
	else
		pwd = ft_strdup(" ~ ");
	if (!g_exit_code)
		prompt = ft_strjoin(P_SUCCESS, P_TAIL, 0, 0b00);
	else
		prompt = ft_strjoin(P_FAIL, P_TAIL, 0, 0b00);
	prompt = ft_strjoin(prompt, pwd, 0, 3);
	return (prompt);
}
