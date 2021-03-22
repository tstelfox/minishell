/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/18 14:29:45 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	redir_multi(void *file_struct)
{
	int		fd;
	t_redir *filename;

	filename = (t_redir*)file_struct;
	fd = open(filename->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	return (fd);
}

int	redirect(t_cmd *cmd)
{
	t_redir	*file_struct;
	int		fd;
	int		out;

	file_struct = (t_redir *)cmd->redirection->content;
	if (file_struct->type == 1)
	{
		fd = open(file_struct->file, O_APPEND | O_RDWR, 0666);
		if (fd == -1)
		{
			cmd_notfound(cmd);
			return (-1);
		}
		out = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		if (file_struct->type == 0) // Ok so need to look into this same shit but with the various kinds of redirections
		{
			fd = ft_lstredir(cmd->redirection, &redir_multi);
		}
			// fd = open(file_struct->file, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else
			fd = open(file_struct->file, O_CREAT | O_APPEND | O_RDWR, 0666);
		out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
	}
	// else // else if (file_struct->type == 1)
	// {
	// 	// Think this shouldn't create files
	// 	fd = open(file_struct->file, O_CREAT | O_RDWR, 0666);
	// }
	return (out);
}
