/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/22 12:40:53 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/07 11:03:58 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	cd_home(t_shell **ghost, t_cmd *cmd)
{
	int	i;

	i = 0;
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], "HOME", ft_strlen("HOME"))
			!= 0 && (ft_strcmp(cmd->args->content, "~") == 0))
		{
			if (chdir(&(*ghost)->env[i][5]) != 0)
				strerror(errno);
		}
		i++;
	}
}

void	cd_root(t_shell **ghost)
{
	int	i;

	i = 0;
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], "HOME", ft_strlen("HOME"))
			!= 0)
		{
			if (chdir(&(*ghost)->env[i][5]) != 0)
				strerror(errno);
		}
		i++;
	}
}

int	run_cd(t_cmd *cmd, t_shell **ghost)
{
	int	i;

	i = 0;
	if (cmd->args == NULL)
	{
		cd_root(ghost);
		return (1);
	}
	if (ft_strcmp(cmd->args->content, "-") == 0)
	{
		ft_putstr_fd("Ghostshell does not support this var expansion\n", 1);
		return (1);
	}
	else if ((ft_strcmp(cmd->args->content, "~") == 0))
		cd_home(ghost, cmd);
	else
	{
		if (chdir(cmd->args->content) != 0)
			cmd_notfound(cmd, NO_FILE, ghost, 0);
	}
	return (1);
}
