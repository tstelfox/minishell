/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dlist.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/21 22:44:00 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/16 14:05:45 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	ft_dlstsize(t_dlist *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	if (!new || !alst)
		return ;
	new->next = *alst;
	if (*alst)
		(*alst)->prev = new;
	*alst = new;
}

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

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	int	len;

	if (!lst)
		return ;
	len = ft_dlstsize(*lst);
	while (--len >= 0)
		ft_dlstdelone(lst, 1, del);
}

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*new_node;

	new_node = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}
