/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 16:09:10 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:37:55 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_start_pos(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j] != '\0')
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	if (i == (int)ft_strlen(s1))
		return (-1);
	return (i);
}

static int	get_end_pos(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] != '\0')
	{
		if (s1[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i + 1);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*new_str;

	if (s1 == 0)
		return (0);
	start = get_start_pos(s1, set);
	if (start == -1)
		return (ft_strdup(""));
	end = get_end_pos(s1, set);
	new_str = ft_substr(s1, start, end - start);
	return (new_str);
}
