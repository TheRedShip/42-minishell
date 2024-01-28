/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:14:12 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/28 15:40:20 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef enum e_error_code
{
	EC_SUCCES = 0,
	EC_FAILED = 1,
	EC_ERRORS = 2,
	EC_NOTNUM = 3,
	EC_TOMAAR = 4
}	t_error_code;

/* MAIN COMMANDS ************************************************************ */

/**
 * @brief			Echoes a string, -n to discard trailing newline.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			ft_echo exit_code.
*/
int			ft_echo(t_command *cmd);

/**
 * @brief			Prints current working directory.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			ft_pwd exit code.		
*/
int			ft_pwd(t_command *cmd);

/**
 * @brief			Change directory.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			ft_cd exit_code.
*/
int			ft_cd(t_command *cmd);

/**
 * @brief			Exits shell.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * @param prompt	Prompt line pointer.
 * @param envp		Linked list pointer (get it by command meta-data if NULL).
 * 
 * @return			ft_exit exit code. 
*/
int			ft_exit(t_command *cmd, char *prompt, t_envvar *envp);

/**
 * @brief			Display environment variables, no order precised.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			ft_env exit_code.
*/
int			ft_env(t_command *cmd);

/**
 * @brief			Exports a environment variable, or display them if no args.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			ft_export exit code.
*/
int			ft_export(t_command *cmd);

/**
 * @brief			Unsets one or more environment variables.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			ft_unset exit code.
*/
int			ft_unset(t_command *cmd);

/* UTILS ******************************************************************** */

/**
 * @brief			Get current working directory.
 * 
 * @return			A pointer to a newly allocated string containing current
 * 					directory absolute path.
*/
char		*ft_get_pwd(void);

/**
 * @brief			Get directory related environment variables.
 *
 * @param envp		Environment variables linked list.
 * 
 * @return			A t_envvar[4] pointer containing references to variables
 * 					HOME, OLDPWD, PWD and SHELL.
*/
t_envvar	**ft_get_directory_vars(t_envvar *envp);

/**
 * @brief			Manage directory change.
 * 
 * @return			chdir exit code.
*/
int			ft_manage_cd(int argc, char **argv, t_envvar **vars);

/**
 * @brief			atoi for exit codes.
 * 
 * @param str		char* to convert.
 * 
 * @return			Numeric value of str n. Subtracted from 256 if negative.
 * 					Modulo 256
*/
long		ft_exit_atoi(char *str);

/**
 * @brief			Check if a string is a numeric value.
 * 
 * @param str		char* to check.
 * 
 * @return			1 if str is a number, 0 otherwise.
*/
int			ft_is_numeric(char *str);

/**
 * @brief			Check if echo option is only 'n's.
 * 
 * @param str		char* to check.
 * 
 * @return			1 if all chars after - are 'n's, 0 otherwise.
*/
int			ft_only_ns(char *str);

/**
 * @brief			Get environment variable string.
 * 
 * @param vars		t_envvar pointer.
 * @param format	Format boolean
 * 
 * @return			Formatted string of all values in *vars, name-leaded,
 * 					':' separated. NULL values set to "" if format is 1.
*/
char		*ft_get_varstring(t_envvar *var, int format);

/**
 * @brief			Get environment variables as a string array.
 * 
 * @param vars		Linked list.
 * @param format	Format boolean
 * 
 * @return			A pointer to char** containing all environment variables.
 * 					name-leaded, ':' separated. 
 * 					NULL values set to "" if format is 1.
*/
char		**ft_get_var_strs(t_envvar *vars, int format);

/**
 * @brief			Sorts a string array by alphabetical order.
 * 
 * @param tab		String array.
 * @param size		Array size.
*/
void		ft_sort_strs_tab(char **tab, int size);

/**
 * @brief			Display environment variables by alphabetical order.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * 
 * @return			EC_SUCCES normally, EC_FAILED in case of NULL allocation.
*/
int			ft_show_export_list(t_command *cmd);

/**
 * @brief			Swap string pointers.
 * 
 * @param a			First string.
 * @param b			Second string
*/
void		ft_swap_strs(char **a, char **b);

/* ************************************************************************** */

#endif