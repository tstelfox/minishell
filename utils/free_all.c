/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 14:55:43 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/19 14:57:11 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	free_all(t_shell **ghost)
{
	int	i;

	i = 0;
	while ((*ghost)->env[i])
	{
		free((*ghost)->env[i]);
		i++;
	}
	free((*ghost)->env);
}
