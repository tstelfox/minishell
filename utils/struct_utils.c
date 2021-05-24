/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 11:25:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/24 10:27:37 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

t_redir	*new_redir(t_shell **ghost, char *file, int type)
{
	t_redir	*new_redir;
	char	*temp;
	int		qts;

	if (check_meta(file))
		error_handler(ghost, SYNTAX_ERROR,
			 "syntax error near unexpected token", file);
	temp = find_env(ghost, file);
	if (check_redir(temp))
		error_handler(ghost, PARSE_ERROR, "ambiguous redirect", NULL);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
	qts = count_quotes(temp);
	if (qts)
	{
		new_redir->file = handle_quotes(ghost, temp, ft_strlen(temp) - qts);
		free(temp);
	}
	else
		new_redir->file = temp;
	new_redir->type = type;
	return (new_redir);
}

t_cmd	*new_command(void)
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	if (!new_command)
		return (NULL);
	new_command->args = NULL;
	new_command->redirection = NULL;
	new_command->type = NULL;
	new_command->seprator_type = 0;
	return (new_command);
}

void	restart_shell(t_shell **ghost)
{
	ft_lstclear(&((*ghost)->tokens), del_content);
	free((*ghost)->tokens);
	ft_lstclear(&((*ghost)->commands), del_commands);
	free((*ghost)->commands);
	(*ghost)->commands = NULL;
	(*ghost)->tokens = NULL;
	(*ghost)->status = PARSE;
	(*ghost)->error = 0;
}

void	assign_shell(t_shell **ghost, char **env)
{
	(*ghost)->first_command = TRUE;
	(*ghost)->current = (*ghost)->history;
	(*ghost)->env = get_envp(env);
	(*ghost)->args = NULL;
	(*ghost)->status = 0;
	twenty_five_lines_max_justifyer(ghost);
	(*ghost)->pipefd[0] = -69;
	(*ghost)->pipefd[1] = -47;
	(*ghost)->error = 0;
	(*ghost)->ret_stat = 0;
	(*ghost)->pid = -99;
	(*ghost)->built_in[0] = "echo";
	(*ghost)->built_in[1] = "cd";
	(*ghost)->built_in[2] = "pwd";
	(*ghost)->built_in[3] = "exit";
	(*ghost)->built_in[4] = "env";
	(*ghost)->built_in[5] = "unset";
	(*ghost)->built_in[6] = "export";
	(*ghost)->g_builtin_f[0] = &run_echo;
	(*ghost)->g_builtin_f[1] = &run_cd;
	(*ghost)->g_builtin_f[2] = &run_pwd;
	(*ghost)->g_builtin_f[3] = &run_exit;
	(*ghost)->g_builtin_f[4] = &run_env;
	(*ghost)->g_builtin_f[5] = &run_unset;
	(*ghost)->g_builtin_f[6] = &run_export;
}

t_shell	*init_shell(char **env)
{
	t_shell	*new_shell;

	new_shell = malloc(sizeof(t_shell));
	if (!new_shell)
		return (NULL);
	ft_bzero(new_shell, sizeof(t_shell));
	new_shell->reins = reins_init();
	if (!new_shell->reins)
	{
		free(new_shell);
		return (NULL);
	}
	assign_shell(&new_shell, env);
	return (new_shell);
}
