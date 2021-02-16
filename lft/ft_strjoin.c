/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 15:51:49 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:34 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
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
	return (ret);
}
