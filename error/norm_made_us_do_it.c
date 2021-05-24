/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   norm_made_us_do_it.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 17:10:18 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/24 10:27:22 by ztan          ########   odam.nl         */
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
