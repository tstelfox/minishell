/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 17:54:37 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:08 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*dest;
	const char		*sorc;

	i = 0;
	dest = dst;
	sorc = src;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		dest[i] = sorc[i];
		i++;
	}
	return (dst);
}
