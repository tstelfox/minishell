/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 11:25:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/25 22:57:54 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	del_content(void *content)
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
	ft_lstclear(&commands->args, del_content);
	ft_lstclear(&commands->redirection, del_redir);
	ft_bzero(commands, sizeof(t_cmd));
	commands->seprator_type = 0;
}

void	del_darray(char **str)
{
	int i;

	i = 0;
	if (str)
	{
		if (str[i])
		{
			while (str[i])
			{
				free(str[i]);
				i++;
			}
		}
		free(str);
	}
}

t_redir	*new_redir(t_shell **ghost, char *file, int type)
{
	t_redir *new_redir;

	if (check_meta(file))
		error_handler(ghost, PARSE_ERROR, "syntax error near unexpected token", file);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
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

void		del_ghost(t_shell **ghost)
{
	if (*ghost)
	{
		if ((*ghost)->current)
		{
			ft_dlstclear(&(*ghost)->current, del_content);
			free((*ghost)->current);
		}
		if ((*ghost)->commands)
		{
			ft_lstclear(&(*ghost)->commands, del_commands);
			free((*ghost)->commands);
		}
		if ((*ghost)->tokens)
		{
			ft_lstclear(&(*ghost)->tokens, del_content);
			free((*ghost)->tokens);
		}
		if ((*ghost)->env)
			del_darray((*ghost)->env);
		if ((*ghost)->line)
			free((*ghost)->line);
		if ((*ghost)->reins)
			reins_destroy((*ghost)->reins);
		free(*ghost);
	}
}

void	get_env(t_shell **ghost, char **envp)
{
	int i = 0;
	while (envp[i])
		i++;
	(*ghost)->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*ghost)->env)
		error_handler(ghost, INTERNAL_ERROR, "failed to allocate space", NULL);
	int k = 0;
	while (envp[k])
	{
		(*ghost)->env[k] = ft_strdup(envp[k]);
		k++;
	}
	(*ghost)->env[k] = 0;
}

void	restart_shell(t_shell **ghost)
{
	ft_lstclear(&(*ghost)->tokens, del_content);
	ft_lstclear(&(*ghost)->commands, del_commands);
	(*ghost)->commands = NULL;
	(*ghost)->tokens = NULL;
	(*ghost)->status = PARSE;
	(*ghost)->error = 0;
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
	new_shell->status = 0;
	new_shell->out = -42;
	new_shell->pipefd[0] = -69;
	new_shell->pipefd[1] = -47;
	// new_shell->error = -46;
	new_shell->error = 0;
	new_shell->ret_stat = 0;
	new_shell->pid = -99;
	return (new_shell);
}