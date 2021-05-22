/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/22 12:49:46 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/22 12:50:08 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	run_pwd(t_cmd *cmd, t_shell **ghost)
{
	char	buff[1024];

	(void)ghost;
	if (cmd->args != NULL)
		return (1);
	if (getcwd(buff, sizeof(buff)) == NULL)
		strerror(errno);
	else
	{
		ft_putstr_fd(buff, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		if ((*ghost)->out != -42)
			dup2((*ghost)->out, STDOUT_FILENO);
		return (1);
	}
	return (0);
}
