/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 21:02:21 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/10 19:57:42 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_words(char **ret, int i)
{
	while (i > 0)
	{
		i--;
		free(ret[i]);
	}
	free(ret);
	return (1);
}

static int	word_num(char const *s, char c)
{
	int counter;
	int i;

	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			counter++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			return (counter);
		i++;
	}
	return (counter);
}

static int	make_words(char const *s, char c, char **ret, int strnum)
{
	int array_i;
	int wordlen;

	array_i = 0;
	while (array_i != strnum)
	{
		wordlen = 0;
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			wordlen++;
			s++;
		}
		ret[array_i] = (char *)malloc(sizeof(char) * (wordlen + 1));
		if (!ret[array_i])
			return (free_words(ret, array_i));
		ft_memcpy(ret[array_i], s - wordlen, wordlen);
		ret[array_i][wordlen] = '\0';
		array_i++;
	}
	ret[array_i] = 0;
	return (0);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	int		strnum;

	if (!s)
		return (NULL);
	strnum = word_num(s, c);
	ret = (char **)malloc(sizeof(char *) * (strnum + 1));
	if (!ret)
		return (NULL);
	if (make_words(s, c, ret, strnum) == 1)
		return (NULL);
	return (ret);
}
