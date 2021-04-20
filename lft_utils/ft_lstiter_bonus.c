/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:22:14 by ztan          #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2021/04/12 12:34:36 by ztan          ########   odam.nl         */
=======
/*   Updated: 2021/04/08 19:01:42 by tmullan       ########   odam.nl         */
>>>>>>> a36cc42d552835b80593c58651af008d9bf91fcb
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
<<<<<<< HEAD
=======

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
		if (temp->next != NULL)
			close(fd);
		temp = temp->next;
	}
	return (fd);
}
>>>>>>> a36cc42d552835b80593c58651af008d9bf91fcb
