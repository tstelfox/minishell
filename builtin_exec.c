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

int	run_echo(char *tokens[])
{
	// Some check to see if there's a Pipe or a redirection or some shiz
	if (tokens[1] == NULL)
		return (0);
	if (ft_strcmp(tokens[1], "-n") == 0)
		//Don't print the newline
	// Depending on flag Do the redirecting shit
	ft_putstr_fd(tokens[1], STDOUT_FILENO); // Simplest case
	return (1);
}

int	run_cd(char *tokens[])
{
	if (tokens[1] == NULL)
		return (0);
	if (chdir(tokens[1]) != 0)
		strerror("Frick ");
	return (1);
}

int	run_pwd(char *tokens[])
{
	char	*buff;

	// if (tokens[1] != NULL)
	// {
	// 	printf("pwd doesn't accept arguments");
	// 	return (0);
	// }
	if (getcwd(buff, sizeof(buff)) == NULL)
		strerror("getcwd error");
	else
	{
		printf("%s\n", buff);
		return (1);
	}
}

int	builtin_exec(char *tokens[])
{
	int	i;

	i = 0;
	if (tokens[0] == NULL)
		return (0);
	while (i < 7)
	{
		if (ft_strcmp(tokens[0], g_builtin[i]) == 0)
			return (g_builtin_f[i]); // Need to integrate the parsing shit into this process
		i++;
	}
	return (0);
}