/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:50:56 by ztan          #+#    #+#                 */
/*   Updated: 2020/09/10 19:05:29 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	int ret;

	ret = 0;
	if (!str)
		return ;
	ret = write(fd, str, ft_strlen(str));
	if (ret < 0)
		exit(0);
}
