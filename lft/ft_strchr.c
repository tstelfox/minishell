/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:58:49 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:30 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	while (i <= (s_len))
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
