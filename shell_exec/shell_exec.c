/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/22 12:36:10 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_echo(t_list *args)
{
	while (args->next)
	{
		ft_putstr_fd(args->content, STDOUT_FILENO);
		ft_putstr_fd(" ", 1);
		args = args->next;
	}
	ft_putstr_fd(args->content, STDOUT_FILENO);
}

int	run_echo(t_cmd *cmd, t_shell **ghost)
{
	t_list *head;

	(void)ghost;
	if (cmd->args == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	head = cmd->args;
	if (ft_strcmp(cmd->args->content, "-n") == 0)
	{
		cmd->args = cmd->args->next;
		print_echo(cmd->args);
	}
	else
	{
		print_echo(cmd->args);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	cmd->args = head;
	return (1);
}

int	run_cd(t_cmd *cmd, t_shell **ghost)
{
	int	i;

	i = 0;
	if (cmd->args == NULL)
		return (1);
	if (ft_strcmp(cmd->args->content, "-") == 0)
	{
		ft_putstr_fd("Ghostshell does not support this var expansion\n", 1);
		return (1);
	}
	else if ((ft_strcmp(cmd->args->content, "~") == 0))
	{
		while ((*ghost)->env[i])
		{
			if (ft_strnstr((*ghost)->env[i], "HOME", ft_strlen("HOME"))
				!= 0 && (ft_strcmp(cmd->args->content, "~") == 0))
			{
				if (chdir(&(*ghost)->env[i][5]) != 0)
					strerror(errno);
			}
			i++;
		}
	}
	else
	{
		if (chdir(cmd->args->content) != 0)
			cmd_notfound(cmd, NO_FILE, ghost, 0);
	}
	return (1);
}

int	run_pwd(t_cmd *cmd, t_shell **ghost)
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
		if ((*ghost)->out != -42)
			dup2((*ghost)->out, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	run_env(t_cmd *cmd, t_shell **ghost)
{
	int	i;

	i = 0;
	if (cmd->args != NULL)
		return (1);
	while ((*ghost)->env[i])
	{
		if (ft_strchr((*ghost)->env[i], '='))
		{
			ft_putstr_fd((*ghost)->env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (1);
}

// int	run_unset(t_cmd *cmd, t_shell **ghost)
// {
// 	int i;
// 	int k = 0;

// 	i = 0;
// 	if (!cmd->args)
// 		return (1);
// 	while (cmd->args->next)
// 	{
// 		int len = ft_strlen(cmd->args->content);
// 		while ((*ghost)->env[i])
// 		{
// 			if (ft_strnstr((*ghost)->env[i], cmd->args->content, len))
// 				k = i;
// 			i++;
// 		}
// 		char **temp;
// 		temp = (char**)malloc(sizeof(char*) * (i));
// 		int j = 0;
// 		for (int i = 0; (*ghost)->env[i]; i++)
// 		{
// 			if (i != k)
// 			{
// 				temp[j] = (*ghost)->env[i];
// 				j++;
// 			}
// 			else
// 				free((*ghost)->env[i]);
// 		}
// 		temp[j] = 0;
// 		free((*ghost)->env);
// 		(*ghost)->env = temp;
// 		cmd->args = cmd->args->next;
// 	}
// 	int len = ft_strlen(cmd->args->content);
// 	while ((*ghost)->env[i])
// 	{
// 		if (ft_strnstr((*ghost)->env[i], cmd->args->content, len))
// 			k = i;
// 		i++;
// 	}
// 	char **temp;
// 	temp = (char**)malloc(sizeof(char*) * (i));
// 	int j = 0;
// 	for (int i = 0; (*ghost)->env[i]; i++)
// 	{
// 		if (i != k)
// 		{
// 			temp[j] = (*ghost)->env[i];
// 			j++;
// 		}
// 		else
// 			free((*ghost)->env[i]);
// 	}
// 	temp[j] = 0;
// 	free((*ghost)->env);
// 	(*ghost)->env = temp;
// 	return(1);
// }

int	shell_exec(t_list *command, t_shell **ghost)
{
	int	i;
	t_cmd	*cmd;

	i = 0;
	cmd = command->content;
	if (command->content == NULL)
		return (0);
	while (1)
	{
		if (cmd->seprator_type == PIPE)
		{
			pipe_exec(command, ghost);
			return (1);
		}
		if (i != 0)
		{
			i = 0;
			command = command->next;
			cmd = command->content;
		}
		while (i < 7)
		{
			// ft_putstr_fd("In here?\n", 1);
			// ft_putstr_fd((*ghost)->built_in[i], STDOUT_FILENO);
			if (ft_strcmp(cmd->type, (*ghost)->built_in[i]) == 0)
			{
				if (cmd->redirection)
				{
					if (redirect(cmd, ghost) == -1)
						return (1);
				}
				if ((*ghost)->in != -42)
					dup2((*ghost)->in, STDIN_FILENO);
				// ft_putnbr_fd((*ghost)->out, 1);
				// (*ghost)->out = redirect(cmd, ghost);
				// if ((*ghost)->out == -1 && cmd->redirection)
				// if (redirect == -1)
				// 	return(1);
				(*ghost)->ret_stat = 0;
				// ft_putstr_fd("In here?\n", 1);
				// ft_putstr_fd((*ghost)->built_in[i], STDOUT_FILENO);
				(*ghost)->g_builtin_f[i](cmd, ghost);
				if ((*ghost)->out != -42)
					dup2((*ghost)->out, STDOUT_FILENO);
				if (!command->next)
				{
					if ((*ghost)->pipefd[0] != -69)
						close((*ghost)->pipefd[0]);
					return (1);
				}
			}
			i++;
		}
		prog_launch(cmd, ghost);
		if ((*ghost)->out != -42)
			dup2((*ghost)->out, STDOUT_FILENO);
		if (!command->next)
		{
			if ((*ghost)->pipefd[0] != -69)
				close((*ghost)->pipefd[0]);
			return (1);
		}
	}
	return (1);
}
