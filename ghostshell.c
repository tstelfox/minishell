/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:03:37 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/15 18:20:11 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"
#define BUFF_SIZE 77

int	main(void)
{
	char	buffer[BUFF_SIZE];
	int		i;

	i = 0;
	while (i < 69) // very nice
	{
		buffer[i] = 'a';
		i++;
	}
	return (buffer[46] == 'a' ? 0 : 69); // BEHOLD THE TERNARY
}
