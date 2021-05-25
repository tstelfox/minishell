/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/25 16:23:39 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	multi_redir(t_cmd *cmd, t_shell **ghost, t_redir *redir)
{
	int		fd;
	t_list	*head;
	t_redir	*next_file;

	head = cmd->redirection;
	if (redir->type == INPUT)
	{
		(*ghost)->error = NO_FILE;
		fd = open(redir->file, O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
		if (cmd->redirection->next)
		{
			cmd->redirection = cmd->redirection->next;
			next_file = cmd->redirection->content;
			if (next_file->type == OUTPUT)
			{
				(*ghost)->in = dup(STDIN_FILENO);
				dup2(fd, STDIN_FILENO);
			}
			cmd->redirection = head;
		}
	}
	else
	{
		if (redir->type == OUTPUT)
			fd = open(redir->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			fd = open(redir->file, O_CREAT | O_APPEND | O_RDWR, 0666);
	}
	close(fd);
	return (0);
}

int	final_redir(t_cmd *cmd, t_shell **ghost, t_redir *redir, t_redir *last_op)
{
	int	fd;

	if (redir->type == INPUT)
	{
		(*ghost)->error = NO_FILE;
		fd = open(redir->file, O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
		if (last_op && last_op->type != INPUT)
		{
			close(fd);
			if (last_op->type == OUTPUT)
				fd = open(last_op->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
			else
				fd = open(last_op->file, O_CREAT | O_APPEND | O_RDWR, 0666);
			(*ghost)->out = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
		}
		else
		{
			(*ghost)->in = dup(STDIN_FILENO);
			dup2(fd, STDIN_FILENO);
		}
	}
	else
	{
		if (redir->type == OUTPUT)
			fd = open(redir->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			fd = open(redir->file, O_CREAT | O_APPEND | O_RDWR, 0666);
		(*ghost)->out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return (0);
}

int	redirect(t_cmd *cmd, t_shell **ghost)
{
	t_redir	*redir;
	t_list	*head;
	t_redir	*last_next;

	head = cmd->redirection;
	redir = (t_redir *)cmd->redirection->content;
	while (cmd->redirection->next)
	{
		if (multi_redir(cmd, ghost, redir) == -1)
		{
			cmd->redirection = head;
			return (-1);
		}
		last_next = redir;
		cmd->redirection = cmd->redirection->next;
		redir = cmd->redirection->content;
	}
	if (final_redir(cmd, ghost, redir, last_next) == -1)
	{
		cmd->redirection = head;
		return (-1);
	}
	cmd->redirection = head;
	return (0);
}
