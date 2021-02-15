/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:40:50 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:36:49 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*free_list(t_list *lst, t_list *data, void (*del)(void *))
{
	del(data);
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	t_list	*data;

	if (!lst)
		return (NULL);
	data = f(lst->content);
	new = ft_lstnew(data);
	if (!new)
		return (free_list(new, data, del));
	lst = lst->next;
	while (lst)
	{
		data = f(lst->content);
		temp = ft_lstnew(data);
		if (!temp)
			return (free_list(new, data, del));
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
