/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:40:39 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:37 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dlen;
	size_t slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= dstsize)
		return (dstsize + slen);
	if (slen < dstsize - dlen)
		ft_memcpy(dst + dlen, src, slen + 1);
	else
		ft_memcpy(dst + dlen, src, dstsize - dlen - 1);
	dst[dstsize - 1] = '\0';
	return (dlen + slen);
}
