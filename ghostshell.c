/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:03:37 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/25 15:28:01 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "ghostshell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFF_SIZE 77

int	main(int argc, char *argv[], char *envp[])
{
	struct stat buf;
	lstat(argv[1], &buf);
	if (S_ISDIR(buf.st_mode))
		printf("GNNNYYEEEET\n");
	// printf("%s\n", buf);
	return (0);
}
