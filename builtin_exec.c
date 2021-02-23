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

char	*g_builtin[4] = {
		"echo",
		"cd",
		"pwd",
		"exit"
		// "export"
		// "unset",
		// "env",
};

int		(*g_builtin_f[4])(t_list *tokens, t_env *env_list) = {
		&run_echo,
		&run_cd,
		&run_pwd,
		&run_exit
};

int	run_echo(t_list *tokens, t_env *env_list)
{
	(void)env_list;
	// Some check to see if there's a Pipe or a redirection or some shiz
	if (tokens->next == NULL)
		return (0);
	// if (ft_strcmp(tokens->next->content, "-n") == 0)
		//Don't print the newline
	// Depending on flag Do the redirecting shit
	ft_putstr_fd(tokens->next->content, STDOUT_FILENO); // Simplest case
	return (1);
}

int	run_cd(t_list *tokens, t_env *env_list)
{
	tokens = tokens->next; //Spaces are list items so need to be skipped
	tokens = tokens->next;
	if (tokens->content == NULL)
		return (0);
	//To deal with ~ need to use the env variable
	else if (ft_strcmp(tokens->content, "~") == 0)
	{
		if (ft_strcmp(env_list->name, "HOME") == 0)
		{
			if (chdir(env_list->content) != 0)
				strerror(errno);
		}
		// printf("chdir returns %d\n", chdir(tokens->content));
	}
	else
	{
		// printf("chdir returns %d\n", chdir(tokens->content));
		if (chdir(tokens->content) != 0)
			strerror(errno);
		// ft_putstr_fd("In here at all lads\n", STDOUT_FILENO);
	}
	return (1);
}

int	run_pwd(t_list *tokens, t_env *env_list)
{
	char	buff[1024];

	(void)tokens;
	(void)env_list;
	// if (tokens[1] != NULL)
	// {
	// 	printf("pwd doesn't accept arguments");
	// 	return (0);
	// }
	if (getcwd(buff, sizeof(buff)) == NULL)
		strerror(errno);
	else
	{
		ft_putstr_fd(buff, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	run_exit(t_list *tokens, t_env *env_list)
{
	(void)tokens;
	(void)env_list;
	// ft_putstr_fd("Please not here yet", STDOUT_FILENO);
	exit(1);
}

int	builtin_exec(t_list *tokens, t_env *env_list)
{
	int	i;

	i = 0;
	if (tokens->content == NULL)
		return (0);
	while (i < 7)
	{
		if (ft_strcmp(tokens->content, g_builtin[i]) == 0)
			return (*g_builtin_f[i])(tokens, env_list); // Need to integrate the parsing shit into this process
		i++;
	}
	return (1);
}
