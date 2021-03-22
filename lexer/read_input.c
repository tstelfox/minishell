/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:26:40 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/22 14:37:37 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	read_line(t_shell **ghost, char **input)
{
	int ret;

	ret = reins_get_input((*ghost)->reins, input);
	if (ret != 1)
	{
		free(*input);
		error_handler(ghost, INTERNAL_ERROR, "failed to get input", NULL);
	}
	store_command(ghost, *input);
	reins_disable((*ghost)->reins);
	ft_putchar_fd('\n', STDOUT_FILENO);
}