/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env_iter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:24:27 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/23 12:24:27 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_enviter(t_env *lst, void (*f)(void *))
{
	t_env *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp);
		temp = temp->next;
	}
}