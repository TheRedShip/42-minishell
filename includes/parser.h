/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:23:29 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/09 13:01:42 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* STRING MANIPULATION ****************************************************** */

/**
 * @brief			Enforce strict quoting.
 * 
 * @param str		Pointer to string to check.
 * @param qs		Carried quote state.
*/
void		ft_quote_enforcer(char **str, t_quote_state qs);

/**
 * @brief			Check for quote syntax error.
 * 
 * @param str		String to check.
 * @param qs		Quote_state.
 * 
 * @return			0 if qs is different of QU_ZERO, 1 otherwise.		
*/
int			ft_quote_syntax(char *str, t_quote_state qs);

/**
 * @brief			Recursively replace $VARS by their values.
 * 
 * @param vars		Linked list.
 * @param str		String to format.
 * @param qs		Carried quote state.
*/
char		*ft_replace_vars(t_envvar *vars, char *str, t_quote_state qs);

/**
 * @brief			Insert environment variable into a string.
 * 
 * @param vars		Linked list.
 * @param result	Actual result string.
 * @param str		String leftovers.
 * @param len		Len pointer (filled with inserted string len).
*/
char		*ft_insert_var(t_envvar *vars, char *result, char *str, int *len);

/**
 * @brief			Dequote a string.
 * 
 * @param str		String adress.
 * @param qs		Quote state.
*/
void		ft_dequote_string(char **str, t_quote_state qs);

/**
 * @brief			Dequote all tokens in a linked list.
 * 
 * @param tokens	Linked list.
*/
void		ft_dequote_tokens(t_token *tokens, t_quote_state qs);

/**
 * @brief			Check if a string starts by a token.
 * 
 * @param str		String to analyze.
 * @param qs		Carried quote state.
 * 
 * @return			1 if the string is headed by a token, 0 otherwise.
*/
int			ft_is_token(char *str, t_quote_state qs);

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
 * 
 * @return			1 if the linked list is valid, 0 otherwise.
*/
int		ft_verify_token(t_token *tokens);

/* WILDCARD ***************************************************************** */

/**
 * @brief			Verify if a string is a wildcard string.
 * 
 * @param str		String to check.
 * 
 * @return			1 if the string contains only *, 0 otherwise.
*/
int			ft_verif_wildcard(char *str);

/**
 * @brief			Get current directory wildcard string.
 * 
 * @return			Wildcard string, not sorted.
*/
char		*ft_wildcard_string(void);

/**
 * @brief			Format a wildcard string by sorting.
 * 
 * @param str		String pointer.
*/
void		ft_format_wildcard(char **str);

/**
 * @brief			Format tokens (wildcard && quotes).
 * 
 * @param tokens	Token linked list adress.
*/
void		ft_format_tokens(t_token **tokens);

/**
 * @brief			Replace a wildcard token by a list of string tokens.
 * 
 * @param head		Token linked list head.
 * @param tokens	Current position in the linked list (pointer).
*/
void		ft_wildcard_token(t_token **head, t_token **tokens);

/* TREE ********************************************************************* */
/**
 * @brief			Recursively build a binary syntax tree.
 * 
 * @param tokens	Tokens linked list.
 * @param env		Environment linked list.
*/
t_node		*ft_build_tree(t_token *tokens, t_envvar **env);

void		treeprint(t_node *root, int space);

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
 * 
*/
int			ft_dqstrlen(char *str);

#endif