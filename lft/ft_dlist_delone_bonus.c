/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlist_delone_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:17:53 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 09:18:06 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_dlist **lst, int position, void (*del)(void *))
{
	t_dlist	*temp;

	if (!lst || position < 1)
		return ;
	temp = (*lst);
	while (position-- > 1)
		temp = temp->next;
	if (!temp)
		return ;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	if (!temp->prev)
		*lst = temp->next;
	del(temp->content);
	temp->content = NULL;
	free(temp);
}
