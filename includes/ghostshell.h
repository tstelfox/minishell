/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/31 16:09:21 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GHOSTSHELL_H
# define GHOSTSHELL_H

/* Big thanks to Thijs (Tishj) and Victor (Vtenneke) for letting us use their
 termcaps (https://github.com/Tishj/reins_termcap) wrapper. */
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
	SYNTAX_ERROR = 4,
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
	NO_FILE = 6,
	BAD_ARG_EXIT = 7,
	NO_ACCESS = 8,
	TOO_MANY_ARGS = 9
};

enum	e_return
{
	ERR = 1,
	EXEC_FAIL = 126,
	NOT_CMD = 127,
	SYNTAX_ERR = 258
};

typedef struct s_redirection
{
	char			*file;
	int				type;
}					t_redir;

typedef struct s_cmd
{
	char			*type;
	t_list			*args;
	t_list			*redirection;
	int				seprator_type;
}					t_cmd;

typedef struct s_shell
{
	t_dlist	*history;
	t_dlist	*current;
	int		first_command;
	t_list	*commands;
	t_list	*tokens;
	t_reins	*reins;
	pid_t	pid;
	char	**args;
	char	**path;
	char	**env;
	int		status;
	int		ret_stat;
	int		out;
	int		in;
	int		red_in;
	int		red_out;
	int		pipefd[2];
	int		out_pipe;
	int		pipenum;
	int		*pipepid;
	int		error;
	char	*built_in[7];
	int		(*g_builtin_f[7])(t_cmd *cmd, struct s_shell **ghost);
}					t_shell;

//---------------------------------shell_exec---------------------------------//
//built-in functions
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

//Programs
int		prog_launch(t_cmd *cmd, t_shell **ghost);
int		shell_exec(t_list *tokens, t_shell **ghost);
char	**get_path(t_cmd *cmd, t_shell **ghost);
void	get_args(t_cmd *cmd, t_shell **ghost);
int		check_dir(t_cmd *cmd, t_shell **ghost);

//Redirection
int		redirect(t_cmd *cmd, t_shell **ghost);
int		ft_lstredir(t_list *lst, int (*f)(void *));
int		open_multi(void *file_struct);
int		redirection_handle(t_shell **ghost, t_cmd *cmd);

// Piping
int		pipe_exec(t_list *command, t_shell **ghost);
int		pipe_loop(t_list *command, t_shell **ghost, int fd_in, int cmd_num);
void	path_launch(t_cmd *cmd, t_shell **ghost);
void	count_and_malloc(t_list *command, t_shell **ghost);
void	where_the_kids_at(t_shell **ghost);

//Signals
void	ctrl_process(int sig);
void	ctrl(int sig);

//Freeing
void	free_arr(char **arr);

//Norm Abominations
void	the_replacing(char *str, char *var, t_shell **ghost, int i);
void	twenty_five_lines_max_justifyer(t_shell **ghost);

//-----------------------------------error------------------------------------//
//error.c
void	*error_handler(t_shell **ghost, int error_code,
			char *error_message, char *arg);
void	cmd_notfound(t_cmd *cmd, int flag, t_shell **ghost, int pipe);

//-----------------------------------parser-----------------------------------//
//parser.c
t_list	*parser(t_shell **ghost);

//read_input.c
char	*read_line(t_shell **ghost);
int		up_function(t_input *line, char *buf, t_hook *hook);
int		down_function(t_input *line, char *buf, t_hook *hook);
int		ctrl_c_function(t_input *line, char *buf, t_hook *hook);

//lexer.c
t_list	*lexer(t_shell **ghost, char *input, char *seperators);

//handle_env.c
void	expand_env(t_shell **ghost, t_list **temp);
char	*find_env(t_shell **ghost, char *str);

//handle_funcs.c
int		handle_syntax(t_shell **ghost, t_list *lst);
int		handle_seperator(t_shell **ghost, t_cmd **command);
int		handle_redir(t_shell **ghost, t_cmd **command);
char	*handle_quotes(t_shell **ghost, char *str, int len);

//------------------------------------utils-----------------------------------//
//parser_utils.c
void	remove_quotes(t_shell **ghost, t_list **list);
int		check_meta(char *str);
int		check_redir(char *str);
int		count_quotes(char *str);

//handle_utils.c
int		check_seperator(t_shell **ghost, t_list *temp);
char	*handle_bigger(t_list *lst);
char	*handle_smaller(t_list *lst);

//env_utils.c
char	**get_envp(char **envp);
int		get_len(char **input, int i);
int		compare_env(char *env, char *str, int len);

//struct_utils.c
t_shell	*init_shell(char **env);
t_redir	*new_redir(t_shell **ghost, char *file, int type);
t_cmd	*new_command(void);
void	restart_shell(t_shell **ghost);

//lst_utils.c
void	free_list(t_list **lst, void (*del)(void *));
void	*copy_data(void	*data);
char	**list_to_arr(t_list *tokens);

//history_utils.c
void	store_command(t_shell **ghost, char *line);
void	init_reins(t_shell **ghost);
void	pass_param(void *param);
void	edit_content(t_dlist **node, char *line, int size);

//del_utils.c
void	del_content(void *content);
void	del_redir(void *list);
void	del_commands(void *list);
void	del_ghost(t_shell **ghost);
void	del_darray(char **str);

//miscellaneous_utils.c
void	free_all(t_shell **ghost);
char	**arr_addback(char **arr, char *str);
char	*ft_strjoinfree(char *s1, char const *s2);

//-----------------------------------debug-----------------------------------//
void	print_data(void *data);
void	print_cmd(t_cmd *data);
void	ft_cmd_lstiter(t_list *lst, void (*f)(t_cmd *));
void	debug_loop(t_shell **ghost);
void	test(void);

#endif
