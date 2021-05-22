/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 16:02:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/20 16:28:15 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*handle_smaller(t_list *lst)
{
	t_list	*temp;
	int		i;
	int		type;

	i = 0;
	type = 0;
	temp = lst;
	while (temp)
	{
		if (!ft_strcmp(temp->content, "<"))
			i++;
		if ((!ft_strcmp(temp->content, ">") && i > 0) || i > 2)
			return (temp->content);
		if (!ft_strcmp(temp->content, "<"))
			if (!temp->next)
				return ("newline");
		if (ft_strcmp(temp->content, "<"))
			i = 0;
		temp = temp->next;
	}
	return (NULL);
}

char	*handle_bigger(t_list *lst)
{
	t_list	*temp;
	int		i;
	int		type;

	i = 0;
	type = 0;
	temp = lst;
	while (temp)
	{
		if (!ft_strcmp(temp->content, ">"))
			i++;
		if ((!ft_strcmp(temp->content, "<") && i > 0) || i > 2)
			return (temp->content);
		if (!ft_strcmp(temp->content, ">"))
			if (!temp->next)
				return ("newline");
		if (ft_strcmp(temp->content, ">"))
			i = 0;
		temp = temp->next;
	}
	return (NULL);
}

int	handle_syntax(t_shell **ghost, t_list *lst)
{
	char	*ret;

	ret = handle_bigger(lst);
	if (ret)
	{
		error_handler(ghost, NO_MULTI_LINE,
			 "syntax error near unexpected token", ret);
		return (1);
	}
	ret = handle_smaller(lst);
	if (ret)
	{
		error_handler(ghost, NO_MULTI_LINE,
			 "syntax error near unexpected token", ret);
		return (1);
	}
	return (0);
}
