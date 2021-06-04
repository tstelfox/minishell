/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:48:13 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/03 12:01:05 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	count_and_malloc(t_list *command, t_shell **ghost)
{
	while (command)
	{
		command = command->next;
		(*ghost)->pipenum++;
	}
	(*ghost)->pipepid = (int *)malloc(sizeof(int) * (*ghost)->pipenum);
}

void	where_the_kids_at(t_shell **ghost, int w_status)
{
	int	i;

	i = 0;
	while (i < (*ghost)->pipenum - 1)
	{
		waitpid((*ghost)->pipepid[i], &w_status, 0);
		i++;
	}
}
