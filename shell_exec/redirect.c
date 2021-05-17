/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/17 15:39:47 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	open_multi(void *file_struct)
{
	int		fd;
	t_redir	*filename;

	filename = (t_redir *)file_struct;
	if (filename->type == 0)
		fd = open(filename->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	else
		fd = open(filename->file, O_CREAT | O_APPEND | O_RDWR, 0666);
	return (fd);
}

int	redirect(t_cmd *cmd, t_shell **ghost)
{
	t_redir	*file_struct;
	t_redir	*next_op;
	int		fd;
	int		fd2;
	int		original;

	file_struct = (t_redir *)cmd->redirection->content;
	if (file_struct->type == 1)
	{
		(*ghost)->error = NO_FILE;
		fd = open(file_struct->file, O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			cmd_notfound(cmd, NO_FILE, ghost, 0);
			return (-1);
		}
		original = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		if (cmd->redirection->next)
		{
			cmd->redirection = cmd->redirection->next;
			next_op = (t_redir *)cmd->redirection->content;
			if (next_op->type == 0)
			{
				fd2 = open(next_op->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
				dup2(fd2, STDOUT_FILENO);
				close(fd2);
			}
			else if (next_op->type == 2)
			{
				fd2 = open(next_op->file, O_CREAT | O_APPEND | O_RDWR, 0666);
				dup2(fd2, STDOUT_FILENO);
				close(fd2);
			}
		}
	}
	else
	{
		// if (file_struct->type == 0)
		fd = ft_lstredir(cmd->redirection, &open_multi);
		// else
		// 	fd = open(file_struct->file, O_CREAT | O_APPEND | O_RDWR, 0666);
		original = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return (original);
}
