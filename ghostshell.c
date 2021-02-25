/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:03:37 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/15 13:03:37 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "ghostshell.h"
#include <stdio.h>
#define BUFF_SIZE 77

int	main(int argc, char *argv[], char *envp[])
{
	for (int i = 0; envp[i]; i++) {

		printf("%s\n", envp[i]);
	}
	return (0);
}
