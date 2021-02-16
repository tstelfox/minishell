/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 13:08:40 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:36:29 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*put_num(int n, int count, char *ret)
{
	int	i;

	i = 0;
	ret[count] = '\0';
	if (n == 0)
		ret[i] = '0';
	if (n < 0)
	{
		ret[i] = '-';
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		ret[count - 1] = (n % 10) + '0';
		n /= 10;
		count--;
	}
	return (ret);
}

char		*ft_itoa(int n)
{
	char	*ret;
	int		temp;
	int		count;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = 0;
	temp = n;
	if (temp == 0)
		count = 1;
	if (temp < 0)
		count++;
	while (temp != 0)
	{
		count++;
		temp = temp / 10;
	}
	ret = malloc(sizeof(char) * (count + 1));
	if (!ret)
		return (NULL);
	return (put_num(n, count, ret));
}
