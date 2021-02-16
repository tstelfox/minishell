/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:08:42 by ztan          #+#    #+#                 */
/*   Updated: 2020/08/24 18:36:03 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int			i;
	long int	sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (((str[i] - '0') + (res * 10)) < res)
			return ((sign == 1) ? -1 : 0);
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return ((int)(res * sign));
}
