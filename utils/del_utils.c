/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   del_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:10:05 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 09:49:27 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	del_content(void *content)
{
	free(content);
	content = NULL;
}

void	del_redir(void *list)
{
	t_redir	*redir;

	redir = list;
	free(redir->file);
	redir->file = NULL;
	redir->type = 0;
	free(redir);
}

void	del_darray(char **str)
{
	int	i;

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

void	del_commands(void *list)
{
	t_cmd	*commands;

	commands = (t_cmd *)list;
	if (commands->type)
	{
		free(commands->type);
		ft_lstclear(&commands->args, del_content);
	}
	if (commands->args)
		free(commands->args);
	if (commands->redirection)
	{
		ft_lstclear(&commands->redirection, del_redir);
		free(commands->redirection);
	}
	commands->seprator_type = 0;
	free(commands);
}

void	del_ghost(t_shell **ghost)
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
		if ((*ghost)->reins)
			reins_destroy((*ghost)->reins);
		free(*ghost);
	}
}
