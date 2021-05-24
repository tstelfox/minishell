/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/24 15:29:07 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	multi_redir(t_cmd *cmd, t_shell **ghost, t_redir *file_struct)
{
	int	fd;

	if (file_struct->type == INPUT)
	{
		(*ghost)->error = NO_FILE;
		fd = open(file_struct->file, O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
		(*ghost)->in = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		if (file_struct->type == OUTPUT)
			fd = open(file_struct->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			fd = open(file_struct->file, O_CREAT | O_APPEND | O_RDWR, 0666);
	}
	close(fd);
	return (0);
}

int	final_redir(t_cmd *cmd, t_shell **ghost, t_redir *file_struct)
{
	int	fd;

	if (file_struct->type == INPUT)
	{
		(*ghost)->error = NO_FILE;
		fd = open(file_struct->file, O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
		(*ghost)->in = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		if (file_struct->type == OUTPUT)
			fd = open(file_struct->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			fd = open(file_struct->file, O_CREAT | O_APPEND | O_RDWR, 0666);
		(*ghost)->out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return (0);
}

int	redirect(t_cmd *cmd, t_shell **ghost)
{
	t_redir	*file_struct;

	file_struct = (t_redir *)cmd->redirection->content;
	while (cmd->redirection->next)
	{
		if (multi_redir(cmd, ghost, file_struct) == -1)
			return (-1);
		cmd->redirection = cmd->redirection->next;
		file_struct = cmd->redirection->content;
	}
	if (final_redir(cmd, ghost, file_struct) == -1)
		return (-1);
	return (0);
}
