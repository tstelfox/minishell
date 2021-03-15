/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 12:45:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/15 11:00:26 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	redirect(t_cmd *cmd)
{
	t_redir	*file_struct;
	int		fd;
	int		out;

	file_struct = (t_redir *)cmd->redirection->content;
	fd = open(file_struct->file, O_CREAT | O_RDWR, 0666);
	out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	return (out);
}
