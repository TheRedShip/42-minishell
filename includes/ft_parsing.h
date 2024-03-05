/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:23:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/05 00:20:35 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

/**
 * @brief			Quote state updater.
 * 
 * @param c			Current character.
 * @param qs		Current auote state adress.
 * 
 * @return			! if quote state changed, 0 otherwise.
*/
int			ft_qs_update(char c, t_qstate *qs);

/**
 * @brief			Tokenize a string.
 * 
 * @param str		String to tokenize.
 * @param qs		Quote state.
 * 
 * @return			t_token linked list.
*/
t_token		*ft_tokenizer(char *str, t_qstate qs);

/* STRING MANIPULATION ****************************************************** */

/**
 * @brief			Enforce strict quoting.
 * 
 * @param str		Pointer to string to check.
 * @param qs		Carried quote state.
*/
void		ft_quote_enforcer(char **str, int tmp_file_fd, t_qstate qs);

/**
 * @brief			Check for syntax error.
 * 
 * @param str		String to check.
 * @param end		String ending.
 * @param qs		Quote_state.
 * 
 * @return			Syntax error char.		
*/
t_qstate	ft_quote_error(char *str, char *end, t_qstate qs);

/**
 * @brief			Get quoted string from bad input.
 * 
 * @param line		Actual prompt line with wrong quote syntax.
 * @param envp		Environment adress to free it in child.
 * @param tmp		Temporary file name.
 * 
 * @return			Quoted string or NULL if error.
*/
int			ft_get_dquote(char *line, t_envvar **env, char *tmp);

/**
 * @brief			Get dquote line from dquote file
 * 
 * @param line		Actual line.
 * @param tmp_file	Temporary file name.
 * @param status	Error code from dquote fork.
 * 
 * @return			Dquote line.
*/
char		*ft_get_dquote_line(char *line, char *tmp_file, int status);

/**
 * @brief			Open dquote prompt, joins and write into tmp file.
 * 
 * @param tmp_fd	Temporary file descritpor.
 * @param qs		Quote state.
 * 
 * @return			Dquote readline return.
*/
char		*ft_open_dquote(int tmp_fd, t_qstate qs);

/**
 * @brief			Replace $VARS by their values if existing.
 * 
 * @param vars		Linked list.
 * @param str		String to format.
 * @param qs		Carried quote state.
*/
void		ft_replace_vars(t_envvar *vars, char **str, t_qstate qs);

/**
 * @brief			Insert environment variable into a string array.
 * 
 * @param vars		Linked list.
 * @param start		String to extract from.
 * @param n			Array to add to.
 * @param qs		Quote state.
*/
void		ft_insert_var(t_envvar *vars, char *start, char ***n, t_qstate qs);

/**
 * @brief			Dequote a string.
 * 
 * @param str		String adress.
 * @param qs		Quote state.
*/
void		ft_dequote_string(char **str, t_qstate qs);

/**
 * @brief			Check if a string starts by a token.
 * 
 * @param str		String to analyze.
 * @param qs		Carried quote state.
 * 
 * @return			1 if the string is headed by a token, 0 otherwise.
*/
int			ft_is_token(char *str, t_qstate qs);

/**
 * @brief			Check if a brace group contains a binary operator.
 * 
 * @param tokens	Token linked list.
 * 
 * @return			1 in case of valid group, 0 otherwise.
*/
int			ft_verif_binop_brace(t_token *tk);

/**
 * @brief			Update linked list, deleting useless brace tokens.
 * 
 * @param tokens	Linked list.
*/
void		ft_remove_braces(t_token **tokens);

/**
 * @brief			Check if a token linked list is valid.
 * 
 * @param tokens	Token linked list.
 * @param err_token	Error token string.
 * 
 * @return			1 if the linked list is valid, 0 otherwise.
*/
int			ft_verify_token(t_token *tokens, char **err_token);

/* WILDCARD ***************************************************************** */

/**
 * @brief			Verify if a string is a wildcard string.
 * 
 * @param str		String to check.
 * @param qs		Quote state.
 * 
 * @return			1 if the string contains only *, 0 otherwise.
*/
int			ft_verify_wildcard(char *str, t_qstate qs);

/**
 * @brief			Get current directory wildcard string.
 * 
 * @param wcstr		wilcard string rule.
 * 
 * @return			Wildcard string array, not sorted.
*/
char		**ft_wildcard_array(char *wcstr);

/**
 * @brief			Format a wildcard string array by sorting.
 * 
 * @param files		String Array pointer.
*/
char		*ft_format_wildcard(char ***str);

/**
 * @brief			Format tokens (wildcard && quotes).
 * 
 * @param tokens	Token linked list adress.
 * @param home		HOME t_envvar pointer.
*/
void		ft_format_tokens(t_token **tokens, t_envvar *home);

/**
 * @brief			Replace a wildcard token by a list of string tokens.
 * 
 * @param head		Token linked list head.
 * @param tokens	Current position in the linked list (pointer).
*/
void		ft_wildcard_token(t_token **head, t_token **tokens);

/**
 * @brief			Replace a string by its wildcard equivalent if there is one.
 * 
 * @param str		String adress.
*/
void		ft_replace_wildcard(char **str);

/* TREE ********************************************************************* */

/**
 * @brief			Recursively build a binary syntax tree.
 * 
 * @param tokens	Tokens linked list.
 * @param env		Environment linked list.
*/
t_node		*ft_build_tree(t_token *tokens, t_envvar **env);

/* UTILS ******************************************************************** */

/**
 * @brief			Get prompt total string.
 * 
 * @param envp		Linked list.
 * 
 * @return			Formatted total prompt string.
*/
char		*ft_get_prompt_string(t_envvar *envp);

/**
 * @brief			Print MinishellRC logo.
 * 
 * @param envp		Envp linked list.
*/
void		ft_print_logo(t_envvar *envp);

/**
 * @brief			Sorts a string array by alphabetical order, 
 * 					not case sensitive.
 * 
 * @param tab		String array.
 * @param size		Array size.
*/
void		ft_sort_lowstrs_tab(char **tab, int size);

/**
 * @brief			Unquoted string len.
 * 
 * @param str		String.
 * 
 * @return			Unquoted len of the string.
*/
int			ft_dqstrlen(char *str);

/**
 * @brief			Skip a part of a string, updating its pointer and qs
 * 
 * @param str		String adress.
 * @param len		Len to skip.
 * @param qs		Quote state.
*/
void		ft_quoted_skip(char **str, int *len, t_qstate *qs);

/**
 * @brief			Splits a string, respecting quoting rules.
 * 
 * @param str		string to split.
 * @param sep		string of separators to cut.
 * 
 * @return			A NULL-terminated string array of str splitted by seps.
*/
char		**ft_quoted_split(char *str, char *sep);

/* ************************************************************************** */

#endif