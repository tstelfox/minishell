/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 14:55:43 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/20 12:48:03 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	free_all(t_shell **ghost)
{
	int	i;

	i = 0;
	while ((*ghost)->path[i])
	{
		free((*ghost)->path[i]);
		i++;
	}
	// free((*ghost)->path);
}
