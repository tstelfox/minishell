/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlist_addback_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:21:07 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 09:21:24 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist	*temp;

	if (!alst)
		return ;
	temp = *alst;
	if (!*alst)
		*alst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}
