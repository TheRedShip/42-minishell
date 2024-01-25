/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:16:25 by rgramati          #+#    #+#             */
/*   Updated: 2024/01/25 11:03:54 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* INCLUDES ***************************************************************** */
# include <unistd.h>
# include <stdlib.h>
/* ************************************************************************** */

/* STRUCT ******************************************************************* */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
/* ************************************************************************** */

/* CHAR ********************************************************************* */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(char c);
/* ************************************************************************** */

/* STRING ******************************************************************* */
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size, int null_term);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_atoi(const char *nptr);
double	ft_atof(char *str, int depth);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsjoin(char **strs, char *sep);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
int		ft_strcspn(char *s, const char *rejects);
char	*ft_strtok(char *str, char *token);
int		ft_wc(char *str, char delim);
int		ft_tab_len(char **tab);
/* ************************************************************************** */

/* MEMORY ******************************************************************* */
void	*ft_memset(void *s, int c, size_t n);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_tab(void **tab);
/* ************************************************************************** */

/* PUT_FD ******************************************************************* */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
/* ************************************************************************** */

/* T_LIST ******************************************************************* */
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_front(t_list **lst,	 t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
/* ************************************************************************** */

/* GNL TLST ***************************************************************** */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_slist
{
	struct s_slist	*next;
	char			*str;
}	t_slist;

char	*get_next_line(int fd);
char	*offset(t_slist *lst);
char	*line_from_list(t_slist **lst);

t_slist	*ft_slstnew(char *str);
void	ft_slstclear(t_slist **lst);
void	ft_slstadd_back(t_slist **lst, t_slist *new);
int		ft_slstcsize(t_slist *lst);
/* ************************************************************************** */

#endif