/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/31 15:45:24 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	open_fd(t_cmd *cmd, t_shell **ghost, t_redir *r)
{
	if (r->type == INPUT)
	{
		(*ghost)->error = NO_FILE;
		if ((*ghost)->red_in > 0)
			close((*ghost)->red_in);
		(*ghost)->red_in = open(r->file, O_APPEND | O_RDWR, 0666);
		if ((*ghost)->red_in == -1)
		{
			if ((*ghost)->red_out != -42)
				close((*ghost)->red_out);
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
	}
	else
	{
		if ((*ghost)->red_out > 0)
			close((*ghost)->red_out);
		if (r->type == OUTPUT)
			(*ghost)->red_out = open(r->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			(*ghost)->red_out = open(r->file, O_CREAT | O_APPEND
					| O_RDWR, 0666);
	}
	return (0);
}

void	dup_fds(t_shell **ghost)
{
	if ((*ghost)->red_in > 0)
	{
		(*ghost)->in = dup(STDIN_FILENO);
		dup2((*ghost)->red_in, STDIN_FILENO);
		close((*ghost)->red_in);
	}
	if ((*ghost)->red_out > 0)
	{
		(*ghost)->out = dup(STDOUT_FILENO);
		dup2((*ghost)->red_out, STDOUT_FILENO);
		close((*ghost)->red_out);
	}
}

int	redirect(t_cmd *cmd, t_shell **ghost)
{
	t_redir	*redir;
	t_list	*head;

	head = cmd->redirection;
	redir = (t_redir *)cmd->redirection->content;
	while (cmd->redirection->next)
	{
		if (open_fd(cmd, ghost, redir) == -1)
		{
			cmd->redirection = head;
			return (-1);
		}
		cmd->redirection = cmd->redirection->next;
		redir = cmd->redirection->content;
	}
	if (open_fd(cmd, ghost, redir) == -1)
	{
		cmd->redirection = head;
		return (-1);
	}
	cmd->redirection = head;
	dup_fds(ghost);
	return (0);
}
