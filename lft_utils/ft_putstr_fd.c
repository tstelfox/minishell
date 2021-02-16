/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:50:56 by ztan          #+#    #+#                 */
/*   Updated: 2021/02/16 00:57:22 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

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
