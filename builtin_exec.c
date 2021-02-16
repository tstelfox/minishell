/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/02/16 13:33:57 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*g_builtin[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
};

int		builtin_exec(char *tokens[])
{
	int i;

	i = 0;
	if (tokens[0] == NULL)
		return (0);
	while(i < 7)
	{
		if (ft_strcmp(tokens[0], g_builtin[i]) == 0)
			return() // Return appropriate function pointer result
		i++;
	}
	return (0);
}