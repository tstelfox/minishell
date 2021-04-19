/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoinfree.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/19 17:05:17 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/19 17:05:24 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char		*ft_strjoinfree(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ret;

	if (!s1)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, s1len);
	ft_strlcpy(ret + s1len, s2, s2len + 1);
	free(s1);
	return (ret);
}
