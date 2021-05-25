/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   norm_made_us_do_it.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 17:10:18 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/25 14:26:18 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	the_replacing(char *str, char *var, t_shell **ghost, int i)
{
	if (ft_strchr(str, '='))
	{
		free((*ghost)->env[i]);
		(*ghost)->env[i] = ft_strdup(str);
	}
	free(var);
}

void	twenty_five_lines_max_justifyer(t_shell **ghost)
{
	(*ghost)->out = -42;
	(*ghost)->in = -42;
}

int	redirection_handle(t_shell **ghost, t_cmd *cmd)
{
	if (cmd->redirection)
	{
		if (redirect(cmd, ghost) == -1)
			return (1);
		if (!cmd->type)
		{
			if ((*ghost)->in != -42)
				dup2((*ghost)->in, STDIN_FILENO);
			if ((*ghost)->out != -42)
				dup2((*ghost)->out, STDOUT_FILENO);
			return (1);
		}
	}
	return (0);
}
