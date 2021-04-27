/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:14:11 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/27 16:57:04 by tmullan       ########   odam.nl         */
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
	ft_putstr_fd("ghostshell: ", output);
	if (flag == DIRECTORY)
	{
		(*ghost)->ret_stat = EXEC_FAIL;
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": is a directory\n", output);
		// ft_putstr_fd(strerror(errno), output);
	}
	else if (flag == NO_ACCESS)
	{
		(*ghost)->ret_stat = EXEC_FAIL;
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), output);
		ft_putstr_fd("\n", 1);
	}
	else if (flag == EXPRT_FAIL)
	{
		(*ghost)->ret_stat = ERR;
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": '", output);
		ft_putstr_fd(cmd->args->content, output);
		ft_putstr_fd("': not a valid identifier\n", output);
	}
	else if (flag == BAD_ARG_EXIT)
	{
		ft_putstr_fd("ghostshell: ", output);
		ft_putstr_fd((char*)cmd->args->content, output);
		ft_putstr_fd(": numeric argument reguired\n", output);
	}
	else if (!cmd->redirection)
	{
		(*ghost)->ret_stat = NOT_CMD;

		// ft_putstr_fd("ghostshell: ", output);
		// ft_putnbr_fd((*ghost)->ret_stat, output);
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": ", output);
		ft_putstr_fd(strerror(errno), output);
		ft_putstr_fd("\n", 1);
	}
	else if (flag == NO_FILE)
	{
		file = (t_redir *)cmd->redirection->content;
		ft_putstr_fd(file->file, output);
		ft_putstr_fd(": No such file or directory\n", output);
		// ft_putstr_fd(strerror(errno), output);
	}
}
