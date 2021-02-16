/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 17:50:14 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:36:10 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ar;

	ar = malloc(size * count);
	if (!ar)
		return (NULL);
	ft_bzero(ar, size * count);
	return (ar);
}
