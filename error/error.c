/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:14:11 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/26 11:21:51 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	*error_handler(t_shell **ghost, int error_code, char *error_message, char *arg)
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
	if (error_code < 0)
	{
		del_ghost(ghost);
		exit(1);
	}
	(*ghost)->error = error_code;
	return (NULL);
}

// void	pipe_err_message(t_cmd *cmd, int flag, t_shell **ghost)

void	cmd_notfound(t_cmd *cmd, int flag, t_shell **ghost, int pipe)
{
	t_redir	*file;
	int		output;

	output = STDOUT_FILENO;
	if (pipe == ERR_PIPE)
		output = (*ghost)->out_pipe;
	// ft_putnbr_fd(flag, 1);
	// if (flag >= 3 && flag != 5)
	ft_putstr_fd("ghostshell: ", output);
	if (flag == DIRECTORY)
	{
		// ft_putstr_fd
		(*ghost)->ret_stat = EXEC_FAIL;
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": is a directory\n", output);
	}
	else if (flag == EXPRT_FAIL)
	{
		(*ghost)->ret_stat = ERR;
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": '", output);
		ft_putstr_fd(cmd->args->content, output);
		ft_putstr_fd("': not a valid identifier\n", output);
	}
	else if (!cmd->redirection)
	{
		(*ghost)->ret_stat = NOT_CMD;

		// ft_putstr_fd("ghostshell: ", output);
		// ft_putnbr_fd((*ghost)->ret_stat, output);
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": command not found\n", output);
	}
	else if (flag == NO_FILE)
	{
		file = (t_redir *)cmd->redirection->content;
		ft_putstr_fd(file->file, output);
		ft_putstr_fd(": No such file or directory\n", output);
	}
}
	// else if (flag == ERR_PIPE)
	// {
	// 	(*ghost)->ret_stat = NOT_CMD;
	// 	ft_putstr_fd("ghostshell: ", (*ghost)->out_pipe);
	// 	ft_putstr_fd(cmd->type, (*ghost)->out_pipe);
	// 	ft_putstr_fd(": command not found\n", (*ghost)->out_pipe);
	// }
