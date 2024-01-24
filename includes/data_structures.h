/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:54 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/24 12:01:19 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

/**
 * @enum			e_token_type
 * @brief			Token type.
 */
typedef enum e_token_type
{
	TK_BRACE = 0,
	TK_BINOP,
	TK_PIPES,
	TK_REDIR,
	TK_UNKNO
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2
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
	int				infile;
	int				outfile;
	char			*path;
	char			**args;
	char			**envp;
}   t_command;


/* T_TOKEN ****************************************************************** */

/**
 * @struct			s_token
 * @brief			Command line token.
 * 
 * @param str		(char *)		Token raw string.
 * @param type		(e_token_type) 	Token identifier (see enum).
 */
typedef struct s_token
{
	char            *str;
	t_token_type    type;
}   t_token;

/**
 * @brief			Initializes a new t_token.
 * 
 * @param str		(char *)		Raw string value.
 * @param type		(e_token_type)	Token identifier (see enum),
 * 
 * @return (t_token *) A pointer to the newly allocated t_token.
 */
t_token	*ft_init_token(char *str, t_token_type type)


/* T_ENVVAR ***************************************************************** */

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
 * @brief			Initializes a new t_envvar.
 * 
 * @param value		(char *)	Variable name on the linked list.
 * 
 * @return (t_envvar *) A pointer to the newly allocated t_envvar.
 */
t_envvar    *ft_init_var(char *value);

/**
 * @brief			Append var to the vars linked list.
 * 
 * @param vars		(t_envvar **)	Linked list.
 * @param var		(t_envvar *)	Element to append.
 */
void		ft_add_var(t_envvar **vars, t_envvar *var);

/**
 * @brief			Remove and destroy variable designed by name from vars,
 * 
 * @param vars		(t_envvar **)	Linked list.
 * @param name		(t_envvar *)	Name of the element to remove.
 */
void		ft_remove_var(t_envvar **env, char *name);

/**
 * @brief			De-allocate a t_envvar.
 * 
 * @param var		(t_envvar *)	Element to free.
 */
void		ft_del_var(t_envvar *var);


/* T_NODE ******************************************************************* */

# define LEFT 0
# define RIGHT 1

/**
 * @struct			s_node
 * @brief			Command line node.
 * 
 * @param rank		(int)		Node rank.
 * @param element	(void *)	Opaque pointer to the node content.
 * @param left		(t_node *)	Left child node.
 * @param right		(t_node *)	Right child node.
 */
typedef struct s_node
{
	int				rank;
	void			*element;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

/**
 * @brief			Initializes a new t_node.
 * 
 * @param rank		(int)		Rank on the tree hierarchy.
 * @param element	(void *)	A pointer to struct content.
 * 
 * @return (t_node *) A pointer to the newly allocated t_node.
 */
t_node	*ft_init_node(int rank, void *element);

/**
 * @brief			Insert a t_node (Parent-wise).
 * 
 * @param tree		(t_node **)	Current root t_node, future child.
 * @param root		(t_node *)	New root t_node.
 * @param side		(int)		Side of root where tree will be inserted.
 */
void	ft_insert_parent(t_node **tree, t_node *root, int side);

/**
 * @brief			Insert a t_node (Child-wise).
 * 
 * @param tree		(t_node **)	Current root t_node, future parent.
 * @param child		(t_node *)	New child t_node.
 * @param side		(int)		Side of tree where child will be inserted.
 */
void	ft_insert_child(t_node **tree, t_node *child, int side);

/**
 * @brief			Associate 2 t_node into one tree and sets tree to \
 * @brief           newly allocated parent.
 * 
 * @param tree		(t_node **)	t_node *1, future left child.
 * @param neigh		(t_node *)	t_node *2, future right child.
 * @param element	(void *)	New root t_node content
 */
void	ft_associate(t_node **tree, t_node *neigh, void *element);

#endif