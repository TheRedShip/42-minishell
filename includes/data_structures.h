/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:54 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/08 18:25:11 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

# define LEFT 0
# define RIGHT 1

/* ENUMS ******************************************************************** */

/**
 * @enum			e_token_type
 * @brief			Token type.
 */
typedef enum e_token_type
{
	TK_STRING = 0b00001,
	TK_BRACES = 0b00010,
	TK_BINOPS = 0b00100,
	TK_PIPEXS = 0b01000,
	TK_REDIRS = 0b10000
}   t_token_type;

/**
 * @enum			e_quote_state
 * @brief			Quote state.
 */
typedef enum e_quote_state
{
	QU_ZERO = 0,
	QU_SINGLE,
	QU_DOUBLE
}	t_quote_state;

/* TYPEDEFS ***************************************************************** */

/**
 * @struct			s_token
 * @brief			Command line token.
 * 
 * @param str		(char *)		Token raw string.
 * @param type		(e_token_type) 	Token identifier (see enum).
 * @param next		(t_token *)		Next Token.
 * @param prev		(t_token *)		Previous Token.
 */
typedef struct s_token
{
	char            *str;
	t_token_type    type;
	struct s_token	*next;
	struct s_token	*prev;
}   t_token;

/**
 * @struct			s_envvar
 * @brief			Environment variable linked list node.
 * 
 * @param name		(char *)		Variable name.
 * @param values	(char **)		Variable values.
 * @param next		(t_envvar *)	Next element.
 */
typedef struct s_envvar
{
	char			*name;
	char			**values;
	struct s_envvar	*next;
}	t_envvar;

/**
 * @struct			s_command
 * @brief			Command descriptor.
 * 
 * @param infile	Input file descriptor
 * @param outfile	Output file descriptor
 * @param path		Command path
 * @param args		Command arguments
 * @param envp		Command environment
 */
typedef struct s_command
{
	int			infile;
	int			outfile;
	char		*path;
	char		**args;
	t_envvar	**envp;
}   t_command;

/**
 * @struct			s_node
 * @brief			Command line node.
 * 
 * @param braced	(int)		Node braced.
 * @param command	(t_command *) pointer to the command, NULL if token.
 * @param token		(t_token *) pointer to the token, NULL if command.
 * @param left		(t_node *)	Left child node.
 * @param right		(t_node *)	Right child node.
 */
typedef struct s_node
{
	int				braced;
	t_command		*command;
	t_token			*token;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

/* T_TOKEN ****************************************************************** */

/**
 * @brief			Initializes a new t_token.
 * 
 * @param str		Raw string value.
 * @param type		Token identifier (see enum),
 * 
 * @return			A pointer to the newly allocated t_token.
 */
t_token		*ft_init_token(char *str, t_token_type type);

/**
 * @brief			Append var to the token linked list.
 * 
 * @param token		Token linked list.
 * @param next		Token to append.
 */
void		ft_add_token(t_token **token, t_token *next);

/**
 * @brief			Remove a token from a linked list.
 * 
 * @param tokens	Adress of element to remove.
*/
void		ft_remove_token(t_token **tokens);

/**
 * @brief			De-allocate a t_token.
 * 
 * @param var		t_token to free.
 */
void		ft_del_token(t_token *token);

/**
 * @brief			De-allocate a t_token linked list.
 * 
 * @param tokens	Linked list to free.
*/
void		ft_clear_token_list(t_token *tokens);

/**
 * @brief			Duplicates a token.
 * 
 * @param token		Token to duplicate.
 * 
 * @return			A pointer to a new t_token, with same string and type,
 * 					next = NULL.
*/
t_token		*ft_dup_token(t_token *token);

/**
 * @brief			Tokenize a string.
 * 
 * @param str		String to tokenize.
 * @param qs		Quote state.
 * 
 * @return			t_token linked list.
*/
t_token		*ft_tokenizer(char *str, t_quote_state qs);

/* T_ENVVAR ***************************************************************** */

/**
 * @brief			Initializes a new t_envvar.
 * 
 * @param value		Variable name on the linked list.
 * 
 * @return			A pointer to the newly allocated t_envvar.
 */
t_envvar    *ft_init_var(char *value);

/**
 * @brief			Append var to the vars linked list.
 * 
 * @param vars		Linked list.
 * @param var		Element to append.
 */
void		ft_add_var(t_envvar **vars, t_envvar *var);

/**
 * @brief			Remove and destroy variable designed by name from vars.
 * 
 * @param vars		Linked list.
 * @param name		Name of the element to remove.
 */
void		ft_remove_var(t_envvar **vars, char *name);

/**
 * @brief			De-allocate a t_envvar.
 * 
 * @param var		t_envvar to free.
 */
void		ft_del_var(t_envvar *var);

/**
 * @brief			De-allocate t_envvar linked list.
 * 
 * @param vars		Linked list.
*/
void		ft_clear_env(t_envvar *vars);

/**
 * @brief			Get t_envvar by searching name inside vars.
 * 
 * @param vars		Linked list.
 * @param name		Name of the variable to search for.
 * 
 * @return			A pointer to the t_envvar with name, NULL either.
*/
t_envvar	*ft_get_var(t_envvar *vars, char *name);

/**
 * @brief			Set t_envvar values to new split of nv.
 * 
 * @param vars		Linked list adress.
 * @param name		Name of the variable to modify.
 * @param string	New string of values, ':' separated.
*/
void		ft_set_var(t_envvar **vars, char *name, char *string);

/**
 * @brief			Exports an environment var into env linked list.
 * 
 * @param cmd		t_cmd pointer with command meta-data.
 * @param tmp		Variable string to export.
 * 
 * @return			Exit code.
*/
int			ft_export_var(t_command *cmd, char *tmp);

/**
 * @brief			Append a string to an environment variable string.
 * 
 * @param vars		Linked list.
 * @param name		Variable name.
 * @param string	String to append.
*/
void		ft_append_var(t_envvar **vars, char *name, char *string);

/**
 * @brief			Get vars linked list size.
 * 
 * @param vars		Linked list.
 * 
 * @return			List size
*/
int			ft_var_size(t_envvar *vars);

/**
 * @brief			Setup t_envvar linked list from envp
 * 
 * @param argv		String array argv.
 * @param envp		String array envp.
 * 
 * @return			A pointer to a newly allocated linked list containing
 * 					environment variables, with name and values.
*/
t_envvar    *ft_setup_env(char **argv, char **envp);

/* T_NODE ******************************************************************* */

/**
 * @brief			Initializes a new t_node.
 * 
 * @param braced		braced on the tree hierarchy.
 * @param command	A pointer to struct command.
 * @param token		A pointer to struct token.
 * 
 * @return			A pointer to the newly allocated t_node.
 */
t_node		*ft_init_node(int braced, t_command *command, t_token *token);

/**
 * @brief			Insert a t_node (Parent-wise).
 * 
 * @param tree		Current root t_node, future child.
 * @param root		New root t_node.
 * @param side		Side of root where tree will be inserted.
 */
void		ft_insert_parent(t_node **tree, t_node *root, int side);

/**
 * @brief			Insert a t_node (Child-wise).
 * 
 * @param tree		Current root t_node, future parent.
 * @param child		New child t_node.
 * @param side		Side of tree where child will be inserted.
 */
void		ft_insert_child(t_node **tree, t_node *child, int side);

/**
 * @brief			Associate 2 t_node into one tree and sets tree to \
 * 		          	newly allocated parent.
 * 
 * @param tree		t_node *1, future left child.
 * @param next		t_node *2, future right child.
 * @param c			New root t_command element.
 * @param t			New root t_token token.
 */
void		ft_associate(t_node **tree, t_node *next, t_command *c, t_token *t);

/**
 * @brief			De-allocate a t_node.
 * 
 * @param tree		t_node to free.
*/
void		ft_del_node(t_node *tree);

/**
 * @brief			De-allocate an entire tree recursively.
 * 
 * @param tree		Tree to free;
*/
void		ft_clear_tree(t_node *tree);

void		ft_display_node(t_node *tree);

/* T_COMMAND **************************************************************** */

/**
 * @brief			Initializes a new t_command.
 * 
 * @param input		Input file descriptor
 * @param output	Output file descriptor
 * @param raw_cmd	Raw command string
 * @param envp		Envp linked list adress.
 * 
 * @return			A pointer to the newly allocated t_command.
 */
t_command	*ft_init_command(int input, int output, char *raw_cmd, t_envvar **envp);

/**
 * @brief			De-allocate a t_command.
 * 
 * @param cmd		t_command to free.
*/
void		ft_del_command(t_command *cmd);

/**
 * @brief			Get command path.
*/
char		*ft_get_path(char *cmd, t_envvar *envp);

/**
 * @brief
*/
void		ft_display_command(t_command *cmd);

#endif