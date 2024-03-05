/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 07:14:12 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 00:23:09 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

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
 * 
 * @return			ft_exit exit code. 
*/
int			ft_exit(t_command *cmd);

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
 * @brief			Back-trim a string excluding to char c
 * 
 * @param str		String to trim.
 * @param c			Char excluded.
 * 
 * @return			Trimmed string.
*/
char		*ft_backtrim(char *str, char c);

/**
 * @brief			Checks if a string is empty or not.
 * 
 * @param str		String to check
 * 
 * @return			0 if str is only composed of whitespaces, 1 otherwise.
*/
int			ft_isnt_empty(char *str);

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
 * @param vars		A t_envvar[4] pointer containing references to variables
 * 					HOME, OLDPWD, PWD.
*/
void		ft_get_directory_vars(t_envvar *envp, t_envvar **vars);

/**
 * @brief			Updates and returns environment variables linked list.
 * 
 * @param env		Linked list to update, NULL to just give back env.
 * 
 * @return			Linked list pointer.
*/
t_envvar	*ft_update_env(t_envvar **env);

/**
 * @brief			Initialize basic environment.
 * 
 * @param env		Empty linked list adress.
 * @param argv		String array argv.
*/
void		ft_create_env(t_envvar **env, char **argv);

/**
 * @brief			Manage directory change.
 * 
 * @return			chdir exit code.
*/
t_error		ft_manage_cd(int argc, char **argv, t_envvar **vars, int out);

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
 * @brief				Exit Handler.
 * 
 * @param exit_code		Exit code.
 * @param ec			Error code (see enum e_error_code).
 * @param cmd			t_command pointer with command meta-data.
*/
void		ft_exit_manager(int exit_code, int ec, t_command *cmd);

/**
 * @brief			Get environment variable string.
 * 
 * @param vars		t_envvar pointer.
 * @param format	Format boolean.
 * @param named		Named boolean.
 * 
 * @return			Formatted string of all values in *vars, name-leaded
 * 					if named is True, ':' separated. "" formatted if format
 * 					is True
*/
char		*ft_get_varstring(t_envvar *var, int format, int named);

/**
 * @brief			Get environment variables as a string array.
 * 
 * @param vars		Linked list.
 * @param format	Format boolean.
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
 * @return			ERR_NOERRS normally, ERR_FAILED in case of NULL allocation.
*/
int			ft_show_export_list(t_command *cmd);

/**
 * @brief			Check environment variable name syntax.
 * 
 * @param str		Name string.
 * 
 * @return			1 if the name syntax is correct, 0 otherwise.
*/
int			ft_export_syntaxer(char *str);

/* ************************************************************************** */

#endif