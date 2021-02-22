/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/17 18:07:38 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GHOSTSHELL_H
# define GHOSTSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "get_next_line.h"




enum	e_status
{
	INVALID_INPUT = -1
};

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_shell
{
	// save tokens
	// comands
	// status
	int		status;
}					t_shell;

typedef	struct		s_env
{
	char			*name;
	void			*content;
	t_env			*next;
}					t_env;

t_env	*g_env;


// built-in functions

int		run_echo(t_list *tokens);
int		run_cd(t_list *tokens);
int		run_pwd(t_list *tokens);
int		run_env(t_list *tokens);
int		run_exit(t_list *tokens);
int		builtin_exec(t_list *tokens);
//globals
char	*g_builtin[4];
int		(*g_builtin_f[4])(t_list *tokens);

// lft_utils
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);




//list
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

// error
void	error_handler(char *error_message);

// lexer
void	read_line(char **input);
t_list	*lexer(char *input);

#endif
