/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:14:11 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/09 15:50:31 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	error_handler(char *error_message)
{
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

void	cmd_notfound(t_cmd *cmd)
{
	ft_putstr_fd("ghostshell: ", 1);
	ft_putstr_fd(cmd->type, 1);
	ft_putstr_fd(": command not found\n", 1);
}