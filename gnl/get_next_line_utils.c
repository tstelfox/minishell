/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 18:21:40 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:35:16 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*line_break(const char *s, int c)
{
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = gnl_strlen(s);
	while (i <= (s_len))
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*copy_line(char *s1, int chr)
{
	size_t	i;
	size_t	size;
	char	*dup;

	i = 0;
	size = 0;
	if (!s1)
		return (NULL);
	while (s1[size] != chr && s1[size] != '\0')
		size++;
	dup = malloc(size + 1);
	if (!dup)
		return (NULL);
	while (s1[i] != chr && s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(char *old, char *new)
{
	char	*joined;
	size_t	i;

	if (!old)
		old = "";
	joined = malloc(sizeof(char) * (gnl_strlen(old) + gnl_strlen(new) + 1));
	if (joined == NULL)
		return (NULL);
	i = 0;
	while (old[i])
	{
		joined[i] = old[i];
		i++;
	}
	while (*new)
	{
		joined[i] = *new;
		i++;
		new++;
	}
	joined[i] = '\0';
	return (joined);
}
