/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:14:11 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/20 17:43:44 by tmullan       ########   odam.nl         */
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

// void	pipe_err_message(t_cmd *cmd, int flag, t_shell **ghost)

void	cmd_notfound(t_cmd *cmd, int flag, t_shell **ghost)
{
	t_redir	*file;

	if (flag >= 3 && flag <= 6)
		ft_putstr_fd("ghostshell: ", 1);
	if (flag == DIRECTORY)
	{
		(*ghost)->ret_stat = EXEC_FAIL;
		ft_putstr_fd(cmd->type, 1);
		ft_putstr_fd(": is a directory\n", 1);
	}
	else if (flag == EXPRT_FAIL)
	{
		(*ghost)->ret_stat = ERR;
		ft_putstr_fd(cmd->type, 1);
		ft_putstr_fd(": '", 1);
		ft_putstr_fd(cmd->args->content, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
	}
	else if (flag == ERR_PIPE)
	{
		(*ghost)->ret_stat = NOT_CMD;
		ft_putstr_fd("ghostshell: ", (*ghost)->out_pipe);
		ft_putstr_fd(cmd->type, (*ghost)->out_pipe);
		ft_putstr_fd(": command not found\n", (*ghost)->out_pipe);
	}
	else if (!cmd->redirection)
	{
		(*ghost)->ret_stat = NOT_CMD;

		ft_putstr_fd("ghostshell: ", 1);
		// ft_putnbr_fd((*ghost)->ret_stat, 1);
		ft_putstr_fd(cmd->type, 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	else if (flag == NO_FILE)
	{
		file = (t_redir *)cmd->redirection->content;
		ft_putstr_fd(file->file, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
}
