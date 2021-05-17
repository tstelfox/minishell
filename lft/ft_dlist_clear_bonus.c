/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlist_clear.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:16:37 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 09:16:50 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	int	len;

	if (!lst || !*lst)
		return ;
	len = ft_dlstsize(*lst);
	while (--len >= 0)
		ft_dlstdelone(lst, 1, del);
}
