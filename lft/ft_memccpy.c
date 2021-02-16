/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 18:14:56 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:00 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*sorc;
	unsigned char	chr;

	i = 0;
	dest = (unsigned char *)dst;
	sorc = (unsigned char *)src;
	chr = (unsigned char)c;
	while (i < n)
	{
		dest[i] = sorc[i];
		if (chr == sorc[i])
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
