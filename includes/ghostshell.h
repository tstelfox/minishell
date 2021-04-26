/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/26 17:03:58 by tmullan       ########   odam.nl         */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft.h"
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
	DIRECTORY = 3,
	EXPRT_FAIL = 4,
	ERR_PIPE = 5,
	NO_FILE = 6
};

enum	e_return
{
	ERR = 1,
	EXEC_FAIL = 126,
	NOT_CMD = 127,
	SYNTAX_ERR = 258
};

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
	t_list	*tokens;
	t_reins	*reins;
	pid_t	pid;
	char	**path;
	char	**env;
	char	*line;
	int		status;
	int		ret_stat; // This is the $? or last exit value.
	int		out;
	int		pipefd[2];
	int		out_pipe;
	int		error;
}					t_shell;

//---------------------------------shell_exec---------------------------------//
// built-in functions
int		run_echo(t_cmd *cmd, t_shell **ghost);
int		run_cd(t_cmd *cmd, t_shell **ghost);
int		run_pwd(t_cmd *cmd, t_shell **ghost);
int		run_env(t_cmd *cmd, t_shell **ghost);
int		run_exit(t_cmd *cmd, t_shell **ghost);
int		run_export(t_cmd *cmd, t_shell **ghost);
int		run_unset(t_cmd *cmd, t_shell **ghost);
void	print_echo(t_list *args);

//globals
char	*g_builtin[7];
int		(*g_builtin_f[7])(t_cmd *cmd, t_shell **ghost);

// Programs
int		prog_launch(t_cmd *cmd, t_shell **ghost);
int		shell_exec(t_list *tokens, t_shell **ghost);
char	**get_path(t_cmd *cmd, t_shell **ghost);

// Redirection
int		redirect(t_cmd *cmd, t_shell **ghost);
int		ft_lstredir(t_list *lst, int (*f)(void *));
int		redir_muti(void *file_struct);

// Piping
int		pipe_exec(t_list *command, t_shell **ghost);
int		first_cmd(pid_t pid, t_list *command, t_shell **ghost, int fd_in, int cmd_num);

//-----------------------------------error------------------------------------//
//error.c
void	*error_handler(t_shell **ghost, int error_code, char *error_message, char *arg);
void	cmd_notfound(t_cmd *cmd, int flag, t_shell **ghost, int pipe);

//-----------------------------------parser-----------------------------------//
//parser.c
void	parser(t_shell **ghost);

//parser_utils.c
void	remove_quotes(t_shell **ghost, t_list **list);
int		check_meta(char *str);
int		handle_colon(t_shell **ghost, t_list **new_lst, t_cmd **command);
int		handle_seperator(t_shell **ghost, t_cmd **command);
int		handle_redir(t_shell **ghost, t_cmd **command);

//read_input.c
void	read_line(t_shell **ghost);
int		up_function(t_input *line, char *buf, t_hook *hook);
int		down_function(t_input *line, char *buf, t_hook *hook);

//lexer.c
t_list	*lexer(t_shell **ghost, char *input, char *seperators);

//handle_env.c
char	**get_envp(char **envp);
// int		replace_env(t_shell **ghost, char **input, int i); //TEST.C
void	expand_env(t_shell **ghost, t_list **temp);

//------------------------------------utils-----------------------------------//
//struct_utils.c
t_shell	*init_shell(char **env);
t_redir	*new_redir(t_shell **ghost, char *file, int type);
t_cmd	*new_command();
void	restart_shell(t_shell **ghost);
void	del_commands(void *list);
void	del_content(void *content);
void	del_darray(char **str);

//lst_utils.c
void	*copy_data(void	*data);
char	**list_to_arr(t_list *tokens);

void	ft_joinlist(t_list **alst, t_list *new);

//history_utils.c
void	store_command(t_shell **ghost, char *line);
void	init_reins(t_shell **ghost);
void	pass_param(void *param);
void	edit_content(t_dlist **node, char *line, int size);

//dlist.c
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);
void	ft_dlstclear(t_dlist **lst, void (*del)(void *));
int		ft_dlstgetpos(t_dlist *lst);
t_dlist *ft_dlstlast(t_dlist *lst);
void	ft_dlstdelone(t_dlist **lst, int position, void (*del)(void *));
void	dreplace(t_dlist **lst, t_dlist *insert, int pos, void (*del)(void *));
void	ft_dlsreversetiter(t_dlist *lst, void (*f)(void *));
int		ft_lstredir(t_list *lst, int (*f)(void *));
void	ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
void	del_ghost(t_shell **ghost);
t_dlist	*ft_dlstfirst(t_dlist *lst);

//tur_utils.c
void	free_all(t_shell **ghost);
char	**arr_addback(char **arr, char *str);
char	*ft_strjoinfree(char *s1, char const *s2);

//-----------------------------------debug-----------------------------------//
void	print_data(void *data);
void	print_cmd(t_cmd *data);
void	ft_cmd_lstiter(t_list *lst, void (*f)(t_cmd *));
void	debug_loop(t_shell **ghost);
void	test();

#endif
