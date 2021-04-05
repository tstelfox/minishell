/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:37:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/05 19:31:01 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_dlstdelone(t_dlist **lst)
{	
	if (!lst)
		return ;
	if ((*lst)->prev)
	{
		printf("current[%s], prev[%s], next[%s]\n", (*lst)->content, (*lst)->prev->content, (*lst)->next->content);
		printf("cont[%s],[%s]\n", (*lst)->prev->next->content, (*lst)->next->prev->content);
		(*lst)->prev->next = (*lst)->next;
		(*lst)->next->prev = (*lst)->prev;
		printf("cont[%s],[%s]\n", (*lst)->prev->next->content, (*lst)->next->prev->content);
	}
	free((*lst)->content);
	(*lst)->content = NULL;
	free(*lst);
}

void	ft_dlstclear(t_dlist **lst)
{
	t_dlist *temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_dlstdelone(&(*lst));
		*lst = temp;
	}
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
	t_dlist *temp;

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
// void	ft_dlstinsert(t_dlist **current, t_dlist **insert)
// {
	
// }

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	t_dlist *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}

t_dlist *ft_dlstfirst(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist *new_node;

	new_node = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

char	**list_to_arr(t_list *tokens)
{
	t_list	*temp;
	char	**ret;
	int		i;

	if (!tokens)
		return (NULL);
	temp = tokens;
	if (!(ret = (char **)malloc(sizeof(char *) * ft_lstsize(tokens) + 1)))
		error_handler(NULL, INTERNAL_ERROR, "malloc fail", NULL);
	i = 0;
	while (temp)
	{
		ret[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
