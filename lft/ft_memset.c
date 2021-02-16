/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:30:56 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:14 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*dst;

	i = 0;
	dst = b;
	while (i < len)
	{
		dst[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
