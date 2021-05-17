/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dlist_addfront_bonus.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 09:21:32 by ztan          #+#    #+#                 */
/*   Updated: 2021/05/17 09:21:43 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	if (!new || !alst)
		return ;
	new->next = *alst;
	if (*alst)
		(*alst)->prev = new;
	*alst = new;
}
