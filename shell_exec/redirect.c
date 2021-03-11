/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/11 13:06:13 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	redirect(t_cmd *cmd)
{
	t_redir	*file_struct;
	file_struct = (t_redir *)cmd->redirection->content;
	int fd = open(file_struct->file, O_CREAT | O_RDWR);
	int out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	return (out);
}
