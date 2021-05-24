/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 16:02:24 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/24 14:11:51 by ztan          ########   odam.nl         */
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

int	check_seperator(t_shell **ghost, t_list *temp)
{
	while (temp)
	{
		if (!ft_strcmp(temp->content, "|") && temp->next)
			if (!ft_strcmp(temp->next->content, ";"))
				error_handler(ghost, SYNTAX_ERROR,
					"syntax error near unexpected token", temp->next->content);
		if (!ft_strcmp(temp->content, ";") && temp->next)
		{
			if (!ft_strcmp(temp->next->content, "|"))
				error_handler(ghost, SYNTAX_ERROR,
					"syntax error near unexpected token", temp->next->content);
			if (!ft_strcmp(temp->next->content, ";"))
				error_handler(ghost, SYNTAX_ERROR,
					"syntax error near unexpected token", temp->next->content);
		}
		if ((*ghost)->error)
			return (1);
		temp = temp->next;
	}
	return (0);
}
