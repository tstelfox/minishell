/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 11:25:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/03/29 15:54:31 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	del_list(void *content)
{
	if (content)
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

// void	restart_shell(t_shell **ghost)
// {
// 	char **env;
// 	t_reins *reins;
// 	t_dlist	*history;
// 	t_dlist	*current;

// 	env = get_envp((*ghost)->env);
// 	reins = (*ghost)->reins;
// 	history = (*ghost)->history;
// 	current = (*ghost)->current;
// 	ft_lstclear(&(*ghost)->tokens, del_list);
// 	ft_lstclear(&(*ghost)->commands, del_commands);
// 	free((*ghost));
// 	*ghost = malloc(sizeof(t_shell));
// 	if (!*ghost)
// 	{
// 		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
// 		return ;
// 	}
// 	(*ghost)->history = history;
// 	(*ghost)->current = current;
// 	(*ghost)->env = env;
// 	(*ghost)->reins = reins;
// 	(*ghost)->commands = NULL;
// 	(*ghost)->tokens = NULL;
// 	(*ghost)->status = PARSE;
// }

void	restart_shell(t_shell **ghost)
{
	char **env;

	env = get_envp((*ghost)->env);
	free((*ghost)->env);//2darray?
	ft_lstclear(&(*ghost)->tokens, del_list);
	ft_lstclear(&(*ghost)->commands, del_commands);
	(*ghost)->env = env;
	(*ghost)->commands = NULL;
	(*ghost)->tokens = NULL;
	(*ghost)->status = PARSE;
}

t_shell	*init_shell(char **env)
{
	t_shell *new_shell;
	
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
	new_shell->first_command = TRUE;
	new_shell->current = new_shell->history;
	new_shell->env = get_envp(env);
	new_shell->status = PARSE;
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
		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
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