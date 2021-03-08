/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/04 13:12:04 by tmullan       ########   odam.nl         */
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

int		(*g_builtin_f[7])(t_cmd *cmd, t_shell *ghost) = {
		&run_echo,
		&run_cd,
		&run_pwd,
		&run_exit,
		&run_env,
		&run_unset,
		&run_export
};

int	run_echo(t_cmd *cmd, t_shell *ghost)
{
	(void)ghost;
	// Some check to see if there's a Pipe or a redirection or some shiz
	if (cmd->args == NULL)
		return (1);
	if (ft_strcmp(cmd->args->content, "-n") == 0)
	{
		cmd->args = cmd->args->next;
		ft_putstr_fd(cmd->args->content, STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd->args->content, STDOUT_FILENO); // Simplest case
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}

int	run_cd(t_cmd *cmd, t_shell *ghost)
{
	int i = 0;
	if (cmd->args->content == NULL)
		return (0);
	else if (ft_strcmp(cmd->args->content, "~") == 0)
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
		if (chdir(cmd->args->content) != 0)
			strerror(errno);
	}
	return (1);
}

int	run_pwd(t_cmd *cmd, t_shell *ghost)
{
	char	buff[1024];

	(void)ghost;
	if (cmd->args != NULL)
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

int	run_env(t_cmd *cmd, t_shell *ghost)
{
	int i = 0;


	if (cmd->args != NULL)
		return (1);
	while (ghost->env[i])
	{
		ft_putstr_fd(ghost->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (1);
}

int	run_export(t_cmd *cmd, t_shell *ghost)
{
	char	**temp; // If the argument has no '=' it shouldn't be made an env

	if (!cmd->args)
		return (1);
	int i = 0;
	while (ghost->env[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	for (int k= 0; ghost->env[k]; k++)
		temp[k] = ft_strdup(ghost->env[k]);
	temp[i] = ft_strdup(cmd->args->content);
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

int	run_unset(t_cmd *cmd, t_shell *ghost)
{
	int i;
	int k = 0;

	i = 0;
	if (!cmd->args)
		return (1);
	int len = ft_strlen(cmd->args->content);
	while (ghost->env[i]) // If the argument is there, find a way to delete it and resize the array (che palle);
	{
		if (ft_strnstr(ghost->env[i], cmd->args->content, len))
			k = i;
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
			j++;
		}
	}
	free(ghost->env);
	ghost->env = (char**)malloc(sizeof(*temp));
	ghost->env = temp;
	// (void)command;
	// (void)ghost;
	return(1);
}

int	run_exit(t_cmd *cmd, t_shell *ghost)
{
	(void)cmd;
	(void)ghost;
	// system ("leaks ghostshell");
	exit(1);
}

int	shell_exec(t_list *command, t_shell *ghost)
{
	int	i;
	int	ret = 0;

	t_cmd	*cmd = (t_cmd*)command->content;

	i = 0;
	if (command->content == NULL)
		return (0);
	while (i < 7)
	{
		if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			ret = (*g_builtin_f[i])(cmd, ghost);
		i++;
	}
	if (ret && cmd->seprator_type != 1)
		return (ret);
	ret = (prog_launch(cmd, ghost));
	if (ret && cmd->seprator_type != 1)
		return (ret);
	else if (command->next != NULL)
		shell_exec(command->next, ghost);
	return (0); // Dunno if this is what is needed here at the end
}
