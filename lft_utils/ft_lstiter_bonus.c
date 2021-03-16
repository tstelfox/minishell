/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:22:14 by ztan          #+#    #+#                 */
/*   Updated: 2021/03/15 18:40:39 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

int		ft_lstredir(t_list *lst, int (*f)(void *))
{
	t_list *temp;
	int		fd;

	if (!lst)
		return (-1);
	temp = lst;
	while (temp)
	{
		fd = f(temp->content);
		temp = temp->next;
	}
	return (fd);
}
