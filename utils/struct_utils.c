/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 11:25:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/03/16 13:33:01 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	del_list(void *content)
{
	free(content);
	content = NULL;
}

void	del_redir(void *list)
{
	t_redir *redir;

	redir = list;
	free(redir->file);
	redir->file = NULL;
	redir->type = 0;
}

void	del_commands(void *list)
{
	t_cmd *commands;

	commands = list;
	free(commands->type);
	ft_lstclear(&commands->args, del_list);
	ft_lstclear(&commands->redirection, del_redir);
	ft_bzero(commands, sizeof(t_cmd));
	commands->seprator_type = 0;
}

void	restart_shell(t_shell *ghost)
{
	char **env;

	env = get_envp(ghost->env);
	ft_lstclear(&ghost->tokens, del_list);
	ft_lstclear(&ghost->commands, del_commands);
	ghost = malloc(sizeof(t_shell));
	if (!ghost)
	{
		error_handler(&ghost, INTERNAL_ERROR, "could not allocate space", NULL);
		return ;
	}
	ghost->env = env;
	ghost->commands = NULL;
	ghost->tokens = NULL;
	ghost->status = 0;
}

t_shell	*init_shell(char **env)
{
	t_shell *new_shell;
	
	new_shell = malloc(sizeof(t_shell));
	ft_bzero(new_shell, sizeof(t_shell));
	new_shell->env = get_envp(env);
	new_shell->status = 0;
	new_shell->out = -42;
	return (new_shell);
}

t_redir	*new_redir(t_shell **ghost, char *file, int type)
{
	t_redir *new_redir;

	if (check_meta(file))
		error_handler(ghost, PARSE_ERROR, "syntax error near unexpected token", file);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
	{
		error_handler(ghost, INTERNAL_ERROR, "could not allocate space", NULL);
		return NULL;
	}
	new_redir->file = ft_strdup(file);
	new_redir->type = type;

	return (new_redir);
}

t_cmd	*new_command()
{
	t_cmd	*new_command;

	new_command = malloc(sizeof(t_cmd));
	if (!new_command)
		return NULL;
	new_command->args = NULL;
	new_command->redirection = NULL;
	new_command->type = NULL;
	new_command->seprator_type = 0;

	return (new_command);
}