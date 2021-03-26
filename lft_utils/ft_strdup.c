/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:02:07 by ztan          #+#    #+#                 */
/*   Updated: 2021/02/17 17:52:17 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
