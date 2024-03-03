/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_structures.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:54 by rgramati          #+#    #+#             */
/*   Updated: 2024/03/03 19:22:18 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DATA_STRUCTURES_H
# define FT_DATA_STRUCTURES_H

# define LEFT 0
# define RIGHT 1

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
	char			*str;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

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
 * @struct			s_redir
 * @brief			Redirection linked list.
 * 
 * @param type		(t_redir_type)	Redirection type.
 * @param filename	(char *)		File name or Here-doc delimiter.
 * @param next		(t_redir *)		Next redirection.
*/
typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/**
 * @struct			s_command
 * @brief			Command descriptor.
 * 
 * @param infile	Input file descriptor.
 * @param outfile	Output file descriptor.
 * @param heredoc	Heredoc file descriptor.
 * @param path		Command path.
 * @param args		Command arguments.
 * @param redirs	Redirections linked list.
 * @param envp		Command environment.
 */
typedef struct s_command
{
	int			infile;
	int			outfile;
	int			heredoc;
	char		*path;
	char		**args;
	t_redir		*redirs;
	t_envvar	**envp;
}	t_command;

/**
 * @struct			s_node
 * @brief			Command line node.
 * 
 * @param command	(t_command *) pointer to the command, NULL if token.
 * @param token		(t_token *) pointer to the token, NULL if command.
 * @param left		(t_node *)	Left child node.
 * @param right		(t_node *)	Right child node.
 */
typedef struct s_node
{
	t_command		*command;
	t_token			*token;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

/** 
 * @struct			s_pid.
 * @brief			PID Stack (LIFO).
 * 
 * @param pid		(pid_t)			PID.
 * @param next		(t_pid *)		Previous PID.
*/
typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

/**
 * @struct			s_pipes.
 * @brief			Pipe Stack (LIFO).
 * 
 * @param fd		(int[2])		Pipe array.
 * @param next		(t_pipes *)		Previous pipe.
*/
typedef struct s_pipes
{
	int				fd[2];
	struct s_pipes	*next;
}	t_pipes;

/**
 * @struct			s_executer
 * @brief			Executer holding t_pid and t_pipes stacks
 * 
 * @param pipes		(t_pipes *)		Pipes linked list.
 * @param next		(t_pid *)		PIDs linked list.
*/
typedef struct s_executer
{
	t_pipes	*pipes;
	t_pid	*pids;
}	t_executer;

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

/* T_ENVVAR ***************************************************************** */

/**
 * @brief			Initializes a new t_envvar.
 * 
 * @param value		Variable name on the linked list.
 * 
 * @return			A pointer to the newly allocated t_envvar.
 */
t_envvar	*ft_init_var(char *value);

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
t_envvar	*ft_setup_env(char **argv, char **envp);

/* T_REDIR ****************************************************************** */

/**
 * @brief			Initializes a new t_redir.
 * 
 * @param tmp		Redirection token from the token list.
 * 
 * @return			A pointer to the newly allocated t_redir.
 */
t_redir		*ft_init_redir(t_token *tmp);

/**
 * @brief			Appends a redir into a linked list.
 * 
 * @param redirs	Linked list head adress.
 * @param next		Redir to append.
 */
void		ft_add_redir(t_redir **redirs, t_redir *next);

/**
 * @brief			De-allocate a t_redir linked list.
 * 
 * @param redirs	Linked list head pointer.
 */
void		ft_clear_redir_list(t_redir *redir);

/* T_COMMAND **************************************************************** */

/**
 * @brief			Initializes a new t_command.
 * 
 * @param redirs	Redirections linked list.
 * @param args		Args string array.
 * @param envp		Envp linked list adress.
 * 
 * @return			A pointer to the newly allocated t_command.
 */
t_command	*ft_init_command(t_redir *redirs, char **args, t_envvar **envp);

/**
 * @brief			De-allocate a t_command.
 * 
 * @param cmd		t_command to free.
*/
void		ft_del_command(t_command *cmd);

/**
 * @brief			Get command path.
 * 
 * @param cmd		Command string.
 * @param envp		Environment linked list.
 * 
 * @return			Command path.
*/
char		*ft_get_path(char *cmd, t_envvar *envp);

/* T_NODE ******************************************************************* */

/**
 * @brief			Initializes a new t_node.
 * 
 * @param command	A pointer to struct command.
 * @param token		A pointer to struct token.
 * 
 * @return			A pointer to the newly allocated t_node.
 */
t_node		*ft_init_node(t_command *command, t_token *token);

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

/* T_PID ******************************************************************** */

/**
 * @brief			Initializes a new t_pid.
 * 
 * @param pid		PID to set, NULL most times.
 * 
 * @return			A pointer to the newly allocated t_pid.
*/
t_pid		*ft_init_pid(pid_t pid);

/**
 * @brief			Pushes a t_pid into a t_pid stack.
 * 
 * @param head		Stack head adress.
 * @param top		t_pid to push in.
*/
void		ft_pid_push(t_pid **head, t_pid *top);

/**
 * @brief			Pop a t_pid from a t_pid stack and returns it.
 * 
 * @param head		Stack head adress.
 * 
 * @return			Popped t_pid.
*/
t_pid		*ft_pid_pop(t_pid **head);

/**
 * @brief			De-allocate a t_pid stack.
 * 
 * @param p_list	t_pid stack.
*/
void		ft_del_pid_list(t_pid *p_list);

/* T_PIPES ****************************************************************** */

/**
 * @brief			Initializes a new t_pipes.
 * 
 * @return			A pointer to the newly allocated t_pipes.
*/
t_pipes		*ft_init_pipes(void);

/**
 * @brief			Pushes a t_pipes into a t_pipes stack.
 * 
 * @param head		Stack head adress.
 * @param top		t_pipes to push in.
*/
void		ft_pipes_push(t_pipes **head, t_pipes *top);

/**
 * @brief			Pop a t_pipes from a t_pipes stack and returns it.
 * 
 * @param head		Stack head adress.
 * 
 * @return			Popped t_pipes.
*/
t_pipes		*ft_pipes_pop(t_pipes **head);

/**
 * @brief			De-allocate a t_pipes, closing file descriptors
 * 
 * @param p			t_pipes to free.
*/
void		ft_del_pipe(t_pipes *p);

/* T_EXECUTER *************************************************************** */

/**
 * @brief			Initializes a new t_executer.
 * 
 * @return			A pointer to the newly allocated t_executer.
 */
t_executer	*ft_init_executer(void);

/* ************************************************************************** */

#endif