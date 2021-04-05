/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 17:12:59 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/05 18:13:26 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_dlsreversetiter(t_dlist *lst, void (*f)(void *))
{
	t_dlist *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->prev;
	}
}

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	test()
{
	t_dlist *list = NULL;

	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item1")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item2")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item3")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item4")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item5")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item6")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item7")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item8")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item9")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item10")));
	ft_dlstiter(list, print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(list), print_data);
	printf("\n");
	ft_dlstdelone(&list->next->next->next);
	ft_dlstiter(list, print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(list), print_data);
	printf("\n");
}