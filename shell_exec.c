/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/04 11:22:44 by tmullan       ########   odam.nl         */
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
		return (1);
	tokens = tokens->next;
	tokens = tokens->next;
	if (ft_strcmp(tokens->content, "-n") == 0)
	{
		tokens = tokens->next;
		tokens = tokens->next;
		ft_putstr_fd(tokens->content, STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(tokens->content, STDOUT_FILENO); // Simplest case
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
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
	char	**temp; // If the argument has no '=' it shouldn't be made an env

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
	// for (int k= 0; ghost->env[k]; k++)
	// 	free(temp[k]);
	// free(temp);
	return (1);
}

int	run_unset(t_list *tokens, t_shell *ghost)
{
	int i;
	int k = 0;

	i = 0;
	if (!tokens->next)
		return (1);
	tokens = tokens->next;
	tokens = tokens->next;
	int len = ft_strlen(tokens->content);
	while (ghost->env[i]) // If the argument is there, find a way to delete it and resize the array (che palle);
	{
		// ft_putstr_fd("Here?", 1);
		if (ft_strnstr(ghost->env[i], tokens->content, len))
		{
			k = i;
			// ft_putstr_fd(ghost->env[i], 1);
			// ft_putstr_fd("\nHere?", 1);
		}
		i++;
	}
	char **temp;
	temp = (char**)malloc(sizeof(char*) * (i - 1));
	int j = 0;
	for (int i = 0; ghost->env[i]; i++)
	{
		if (i != k)
		{
			temp[j] = ghost->env[i];
			// ft_putstr_fd(ghost->env[i], 1);
			// ft_putstr_fd("\n", 1);
			j++;
		}
	}
	free(ghost->env);
	ghost->env = (char**)malloc(sizeof(*temp));
	ghost->env = temp;
	// (void)tokens;
	// (void)ghost;
	return(1);
}

int	run_exit(t_list *tokens, t_shell *ghost)
{
	(void)tokens;
	(void)ghost;
	// system ("leaks ghostshell");
	exit(1);
}

int	shell_exec(t_list *tokens, t_shell *ghost)
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
	return(prog_launch(tokens, ghost));
	// ft_putstr_fd("ghostshell: ", 1);
	// ft_putstr_fd(tokens->content, 1);
	// ft_putstr_fd(": command not found\n", 1);
	return (1);
}
