/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/10 14:49:29 by zenotan       ########   odam.nl         */
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
# include <fcntl.h>
# include "get_next_line.h"
# include "reins.h"

enum	e_status
{
	PARSE = 0,
	EXECUTE = 1,
	FINISHED = 2,
};

enum	e_errors
{
	INTERNAL_ERROR = -1,
	INIT_ERROR = -2,
	NO_MULTI_LINE = 1,
	INVALID_ENV = 2,
	PARSE_ERROR = 3,
};

enum	e_types
{
	TRUE = 1,
	FALSE = 0,
	INPUT = 1,
	OUTPUT = 0,
	OUTPUT_ADD = 2,
	SEPERATOR = 1,
	PIPE = 2,
};

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_dlist
{
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef	struct 		s_redirection
{
	char			*file;
	int				type;
}					t_redir;

typedef struct 		s_cmd
{
	char			*type;
	t_list			*args;
	t_list			*redirection;
	int				seprator_type;
}					t_cmd;


typedef struct		s_shell
{
	t_dlist	*history;
	t_dlist	*current;
	int		first_command;
	t_list	*commands;
	t_dlist	*tokens;
	t_reins	*reins;
	// char	**tokens;
	// comands
	// status
	pid_t	pid;
	char	**env;
	char	*line;
	int		status;
	int		error;
	int		out;
}					t_shell;

// built-in functions
int		run_echo(t_cmd *cmd, t_shell *ghost);
int		run_cd(t_cmd *cmd, t_shell *ghost);
int		run_pwd(t_cmd *cmd, t_shell *ghost);
int		run_env(t_cmd *cmd, t_shell *ghost);
int		run_exit(t_cmd *cmd, t_shell *ghost);
int		run_export(t_cmd *cmd, t_shell *ghost);
int		run_unset(t_cmd *cmd, t_shell *ghost);
void	print_echo(t_list *args);

//globals
char	*g_builtin[7];
int		(*g_builtin_f[7])(t_cmd *cmd, t_shell *ghost);

// Programs
int		prog_launch(t_cmd *cmd, t_shell *ghost);
int		shell_exec(t_list *tokens, t_shell *ghost);
char	**get_path(t_cmd *cmd, t_shell *ghost);

// Redirection
int		redirect(t_cmd *cmd);
int		ft_lstredir(t_list *lst, int (*f)(void *));
int		redir_muti(void *file_struct);

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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_bzero(void *s, size_t n);

//list
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	**list_to_arr(t_list *tokens);

// error
void	error_handler(t_shell **ghost, int error_code, char *error_message, char *arg);
void	cmd_notfound(t_cmd *cmd);

// lexer
void	read_line(t_shell **ghost);
int		up_function(t_input *line, char *buf, t_hook *hook);
int		down_function(t_input *line, char *buf, t_hook *hook);
// void	lexer(t_shell **shell, char *input);
void	lexer(t_shell **shell);

// parser
void	parser(t_shell **ghost);
// char	**get_envp(char **envp);
int		check_meta(char *str);
void	handle_env(t_shell **ghost, char **content);

// struct_utils
t_shell	*init_shell(char **env);
t_redir	*new_redir(t_shell **ghost, char *file, int type);
t_cmd	*new_command();
void	restart_shell(t_shell **ghost);
void	del_commands(void *list);
void	del_content(void *content);
void	del_darray(char **str);

// lst_utils
void	*copy_data(void	*data);
// char	**dlist_to_arr(t_dlist *tokens);
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);
void	ft_dlstclear(t_dlist **lst, void (*del)(void *));
int		ft_dlstgetpos(t_dlist *lst);
t_dlist *ft_dlstlast(t_dlist *lst);
void	ft_dlstdelone(t_dlist **lst, int position, void (*del)(void *));
void	dreplace(t_dlist **lst, t_dlist *insert, int pos, void (*del)(void *));
void	ft_dlsreversetiter(t_dlist *lst, void (*f)(void *));

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
void	del_ghost(t_shell **ghost);
t_dlist	*ft_dlstfirst(t_dlist *lst);

//	history_utils
void	store_command(t_shell **ghost, char *line);
void	init_reins(t_shell **ghost);
void	pass_param(void *param);
void	edit_content(t_dlist **node, char *line, int size);


//debug
void	print_data(void *data);
void	print_cmd(t_cmd *data);
void	ft_cmd_lstiter(t_list *lst, void (*f)(t_cmd *));
void	debug_loop(t_shell **ghost);
void	test();

#endif
