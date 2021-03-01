/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exec.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/01 13:42:23 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	*g_builtin[7] = {
		"echo",
		"cd",
		"pwd",
		"exit",
		"env",
		"unset",
		"export"
};

int		(*g_builtin_f[7])(t_list *tokens, t_shell *ghost) = {
		&run_echo,
		&run_cd,
		&run_pwd,
		&run_exit,
		&run_env,
		&run_unset,
		&run_export
};

int	run_echo(t_list *tokens, t_shell *ghost)
{
	(void)ghost;
	// Some check to see if there's a Pipe or a redirection or some shiz
	if (tokens->next == NULL)
		return (0);
	// if (ft_strcmp(tokens->next->content, "-n") == 0)
		//Don't print the newline
	// Depending on flag Do the redirecting shit
	ft_putstr_fd(tokens->next->content, STDOUT_FILENO); // Simplest case
	return (1);
}

int	run_cd(t_list *tokens, t_shell *ghost)
{
	tokens = tokens->next; //Spaces are list items so need to be skipped
	tokens = tokens->next;
	int i = 0;
	if (tokens->content == NULL)
		return (0);
	else if (ft_strcmp(tokens->content, "~") == 0)
	{
		while (ghost->env[i])
		{
			if (ft_strnstr(ghost->env[i], "HOME", ft_strlen("HOME")) != 0)
			{
				if (chdir(&ghost->env[i][5]) != 0)
					strerror(errno);
			}
			i++;
		}
	}
	else
	{
		if (chdir(tokens->content) != 0)
			strerror(errno);
	}
	return (1);
}

int	run_pwd(t_list *tokens, t_shell *ghost)
{
	char	buff[1024];

	(void)tokens;
	(void)ghost;
	if (tokens->next != NULL)
		return (1);
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

int	run_env(t_list *tokens, t_shell *ghost)
{
	(void)tokens;
	int i = 0;


	if (tokens->next != NULL)
		return (1);
	while (ghost->env[i])
	{
		ft_putstr_fd(ghost->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (1);
}

int	run_export(t_list *tokens, t_shell *ghost)
{
	char	**temp;

	if (!tokens->next)
		return (1);
	int i = 0;
	while (ghost->env[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	for (int k= 0; ghost->env[k]; k++)
		temp[k] = ft_strdup(ghost->env[k]);
	tokens = tokens->next;
	tokens = tokens->next; //remember this time
	temp[i] = ft_strdup(tokens->content);
	temp[i + 1] = 0;
	for (int k= 0; ghost->env[k]; k++) //Just make a fucking freeing function FFS
		free(ghost->env[k]);
	free (ghost->env);
	ghost->env = NULL;
	ghost->env = (char **)malloc(sizeof(*temp));
	ghost->env = temp;
	for (int k= 0; ghost->env[k]; k++)
		free(temp[k]);
	free(temp);
	return (1);
}

int	run_unset(t_list *tokens, t_shell *ghost)
{
	(void)tokens;
	(void)ghost;
	return(1);
}

int	run_exit(t_list *tokens, t_shell *ghost)
{
	(void)tokens;
	(void)ghost;
	system ("leaks ghostshell");
	// ft_putstr_fd("Please not here yet", STDOUT_FILENO);
	exit(1);
}

int	builtin_exec(t_list *tokens, t_shell *ghost)
{
	int	i;

	i = 0;
	if (tokens->content == NULL)
		return (0);
	while (i < 7)
	{
		if (ft_strcmp(tokens->content, g_builtin[i]) == 0)
			return (*g_builtin_f[i])(tokens, ghost); // Need to integrate the parsing shit into this process
		i++;
	}
	return (1);
}
