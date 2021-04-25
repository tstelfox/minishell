/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:37:13 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/25 23:02:21 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_joinlist(t_list **alst, t_list *new)
{
	t_list *temp;

	if (!alst)
		return ;
	temp = *alst;
	// ft_putstr_fd("temp in join: ", STDOUT_FILENO);
	// ft_lstiter(new, print_data);
	// printf("\n");
	if (!*alst)
		*alst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	*copy_data(void	*data)
{
	char *str;

	str = data;
	return (ft_strdup(str));
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
