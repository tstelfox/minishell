/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   err_msg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 17:39:38 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/17 17:03:09 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_error(t_cmd *cmd, int output)
{
	ft_putstr_fd(cmd->type, output);
	ft_putstr_fd(": ", output);
	ft_putstr_fd(cmd->args->content, output);
}

void	file_error(t_cmd *cmd, int output, t_shell **ghost)
{
	t_redir	*file;

	(*ghost)->ret_stat = 1;
	if (cmd->redirection)
	{
		file = (t_redir *)cmd->redirection->content;
		ft_putstr_fd(file->file, output);
	}
	else
		print_error(cmd, output);
	ft_putstr_fd(": No such file or directory\n", output);
}

void	generic_error(t_cmd *cmd, int output, t_shell **ghost)
{
	(*ghost)->ret_stat = NOT_CMD;
	ft_putstr_fd(cmd->type, output);
	ft_putstr_fd(":", output);
	if (errno == EACCES)
	{
		ft_putchar_fd(' ', output);
		ft_putstr_fd(strerror(errno), output);
	}
	else
		ft_putstr_fd(" command not found", output);
	ft_putstr_fd("\n", output);
}

void	export_error(t_cmd *cmd, int output, t_shell **ghost)
{
	(*ghost)->ret_stat = ERR;
	ft_putstr_fd(cmd->type, output);
	ft_putstr_fd(": '", output);
	ft_putstr_fd(cmd->args->content, output);
	ft_putstr_fd("': not a valid identifier\n", output);
}

void	cmd_notfound(t_cmd *cmd, int flag, t_shell **ghost, int output)
{
	output = STDOUT_FILENO;
	if (cmd->seprator_type == PIPE)
		output = (*ghost)->out_pipe;
	ft_putstr_fd("ghostshell: ", output);
	if (flag == DIRECTORY)
	{
		(*ghost)->ret_stat = EXEC_FAIL;
		ft_putstr_fd(cmd->type, output);
		ft_putstr_fd(": is a directory\n", output);
	}
	else if (flag == EXPRT_FAIL)
		export_error(cmd, output, ghost);
	else if (flag == TOO_MANY_ARGS)
		ft_putstr_fd("exit: too many arguments\n", output);
	else if (flag == BAD_ARG_EXIT)
	{
		print_error(cmd, output);
		ft_putstr_fd(": numeric argument reguired\n", output);
	}
	else if (flag == NO_FILE)
		file_error(cmd, output, ghost);
	else
		generic_error(cmd, output, ghost);
}
