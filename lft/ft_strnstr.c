/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:06:04 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:51 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_compare(const char *h, const char *n, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && h[i] != '\0' && n[i] != '\0')
	{
		if (h[i] != n[i])
			break ;
		i++;
	}
	if (n[i] == '\0')
		return (0);
	return (1);
}

char			*ft_strnstr(const char *haystack, const char *needle, size_t l)
{
	size_t	i;

	if (needle[0] == 0)
		return ((char *)haystack);
	if (l == 0)
		return (0);
	i = 0;
	while (haystack[i] != '\0' && l > 0)
	{
		if (ft_compare(haystack + i, needle, l) == 0)
			return ((char *)(haystack + i));
		i++;
		l--;
	}
	return (0);
}
