/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ghostshell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 13:04:04 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/16 01:11:26 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GHOSTSHELL_H
# define GHOSTSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "get_next_line.h"

//globals
int		(*g_builtin_f[7])(char *tokens[]) = {
		&run_echo,
		&run_cd,
		&run_pwd
};

char	*g_builtin[7] = {
		"echo",
		"cd",
		"pwd",
		// "export",
		// "unset",
		// "env",
		// "exit"
};

// lft_utils
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *str, int fd);
int		ft_strcmp(const char *str1, const char *str2);

// built-in functions

int		run_echo(char *tokens[]);
int		run_cd(char *tokens[]);
int		run_pwd(char *tokens[]);

#endif
