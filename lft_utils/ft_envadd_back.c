/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 12:51:06 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/23 12:51:06 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_envaddback(t_env **lst, t_env *item)
{
	t_env *temp;

	if (!lst)
		return ;
	temp = *lst;
	if (!*lst)
		*lst = item;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = item;
	}
}