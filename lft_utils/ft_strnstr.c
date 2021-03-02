/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 16:33:20 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/23 16:33:20 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	d;

	i = 0;
	d = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while ((i - d < len) && (haystack[i] != '\0'))
	{
		while ((haystack[i] != needle[0]) && (i < len) \
				&& (haystack[i] != '\0'))
			i++;
		d = 0;
		while ((haystack[i] == needle[d]) && (i < len))
		{
			i++;
			d++;
			if (needle[d] == '\0')
				return ((char *)&haystack[i - d]);
		}
	}
	return (0);
}