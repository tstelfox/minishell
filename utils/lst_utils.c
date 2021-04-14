/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:37:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/12 12:35:10 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	*copy_data(void	*data)
{
	char *str;

	str = data;
	return (ft_strdup(str));
}

int	ft_dlstsize(t_dlist *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int		ft_dlstgetpos(t_dlist *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->prev;
		i++;
	}
	return (i);
}

t_dlist *ft_dlstfirst(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_dlist *ft_dlstlast(t_dlist *lst)
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

void	ft_dlstdelone(t_dlist **lst, int position, void (*del)(void *))
{
	t_dlist *temp;

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
	int		len;

	if (!lst)
		return ;
	len = ft_dlstsize(*lst);
	while (--len >= 0)
		ft_dlstdelone(lst, 1, del);
}

static t_dlist	*free_dlist(t_dlist *lst, t_dlist *data, void (*del)(void *))
{
	del(data);
	ft_dlstclear(&lst, del);
	return (NULL);
}

t_dlist			*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new;
	t_dlist	*temp;
	t_dlist	*data;

	if (!lst)
		return (NULL);
	data = f(lst->content);
	new = ft_dlstnew(data);
	if (!new)
		return (free_dlist(new, data, del));
	lst = lst->next;
	while (lst)
	{
		if (f)
			data = f(lst->content);
		temp = ft_dlstnew(data);
		if (!temp)
			return (free_dlist(new, data, del));
		ft_dlstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}

void	dreplace(t_dlist **lst, t_dlist *insert, int pos, void (*del)(void *))
{
	t_dlist	*last;
	t_dlist	*temp;
	t_dlist *copy;
	
	if (!insert || !*lst || pos < 1)
		return ;
	temp = (*lst);
	copy = ft_dlstmap(insert, copy_data, del);
	last = ft_dlstlast(copy);
	while (pos-- > 1)
		temp = temp->next;
	if (!temp)
		return ;
	if (temp->prev)
	{
		copy->prev = temp->prev;
		temp->prev->next = copy;
	}
	if (temp->next)
	{
		last->next = temp->next;
		temp->next->prev = last;
	}
	if (!temp->prev)
		*lst = copy;
	del(temp->content);
	temp->content = NULL;
	free(temp);
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
