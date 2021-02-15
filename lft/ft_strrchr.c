/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 16:01:41 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:53 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	i = ft_strlen(s);
	while (str[i] != ch)
	{
		i--;
		if (i < 0)
			return (0);
	}
	return (str + i);
}
