/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:14:11 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/29 16:53:44 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	error_handler(t_shell **ghost, int error_code, char *error_message, char *arg)
{
	write(STDERR_FILENO, "ghostshell: ", 12);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	if (arg)
	{
		write(STDERR_FILENO, "`", 1);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "'", 1);
	}
	write(STDERR_FILENO, "\n", 1);
	(*ghost)->status = error_code;
	exit(1);
}

void	cmd_notfound(t_cmd *cmd)
{
	ft_putstr_fd("ghostshell: ", 1);
	if (!cmd->redirection)
	{
		ft_putstr_fd(cmd->type, 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	else
	{
		t_redir	*file;
		file = (t_redir *)cmd->redirection->content;
		ft_putstr_fd(file->file, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
}