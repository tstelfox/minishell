/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/02 16:32:01 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GHOSTSHELL_H
# define GHOSTSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
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
	pid_t	pid;
	char	**env;
	int		status;
}					t_shell;

// built-in functions

int		run_echo(t_list *tokens, t_shell *ghost);
int		run_cd(t_list *tokens, t_shell *ghost);
int		run_pwd(t_list *tokens, t_shell *ghost);
int		run_env(t_list *tokens, t_shell *ghost);
int		run_exit(t_list *tokens, t_shell *ghost);
int		run_export(t_list *tokens, t_shell *ghost);
int		run_unset(t_list *tokens, t_shell *ghost);
int		builtin_exec(t_list *tokens, t_shell *ghost);
//globals
char	*g_builtin[7];
int		(*g_builtin_f[7])(t_list *tokens, t_shell *ghost);

// Programs
int	prog_launch(t_list *tokens, t_shell *ghost);

// lft_utils
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);




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
