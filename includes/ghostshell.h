/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/16 11:45:24 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GHOSTSHELL_H
# define GHOSTSHELL_H

# include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_shell
{
	// save tokens
	// comands
	// status
}				t_shell;


// lft_utils
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *str, int fd);


#endif
