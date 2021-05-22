/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/22 12:49:34 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/22 12:49:59 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	run_env(t_cmd *cmd, t_shell **ghost)
{
	int	i;

	i = 0;
	if (cmd->args != NULL)
		return (1);
	while ((*ghost)->env[i])
	{
		if (ft_strchr((*ghost)->env[i], '='))
		{
			ft_putstr_fd((*ghost)->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (1);
}
