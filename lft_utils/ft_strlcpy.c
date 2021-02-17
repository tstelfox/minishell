/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:17:31 by ztan          #+#    #+#                 */
/*   Updated: 2021/02/17 17:52:27 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t slen;
	size_t i;

	if (!src || !dst)
		return (0);
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	i = 0;
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}
