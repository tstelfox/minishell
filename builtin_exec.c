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
		// "export",
		// "unset",
		// "env",
		// "exit"
};

int	run_echo(char *tokens[])
{
	return (0);
}

int	run_ch(char *tokens[])
{
	if (tokens[1] == NULL)
	{
		printf("No second argument ?");
		return (0);
	}
	if (chdir(tokens[1]) != 0)
		strerror("Frick ");
	return (1);
}

int	run_pwd(char *tokens[])
{
	char *buff;

	if (tokens[1] != NULL)
	{
		printf("pwd doesn't accept arguments");
		return (0);
	}
	if (getcwd(buff, sizeof(buff)) == NULL)
		strerror("getcwd error");
	else
	{
		printf("%s\n", buff);
		return(1);
	}
}

int		(*g_builtin_f[7])(char *tokens[]) = {
		&run_echo,
		&run_ch,
		&run_pwd
};

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
