/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlist_size_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:23:20 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 09:23:30 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
