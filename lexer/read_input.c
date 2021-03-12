/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:26:40 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/13 00:32:23 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	read_line(char **input)
{
	// this also needs to read from a file?
	int ret;
	char *tty = ttyname(STDIN_FILENO);
	ret = get_next_line(STDOUT_FILENO, input);
	if (ret == -1)
	{
		free(*input);
		/* err handler */
	}
}