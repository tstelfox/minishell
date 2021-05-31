/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 15:48:13 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/31 15:50:12 by tmullan       ########   odam.nl         */
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

void	where_the_kids_at(t_shell **ghost)
{
	int	i;
	int	status;

	i = 0;
	while (i < (*ghost)->pipenum)
	{
		waitpid((*ghost)->pipepid[i], &status, 0);
		i++;
	}
}
