/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/22 18:14:09 by tmullan       ########   odam.nl         */
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

int		(*g_builtin_f[7])(t_cmd *cmd, t_shell **ghost) = {
		&run_echo,
		&run_cd,
		&run_pwd,
		&run_exit,
		&run_env,
		&run_unset,
		&run_export
};

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
	(void)ghost;
	if (cmd->args == NULL)
		return (1);
	if (ft_strcmp(cmd->args->content, "-n") == 0)
	{
		cmd->args = cmd->args->next;
		print_echo(cmd->args);
			// ft_putstr_fd(cmd->args->content, STDOUT_FILENO);
	}
	else
	{
		print_echo(cmd->args);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}

int	run_cd(t_cmd *cmd, t_shell **ghost)
{
	int i = 0;
	if (cmd->args == NULL)
		return (1);
	else if ((ft_strcmp(cmd->args->content, "~") == 0)) // || (ft_strcmp(cmd->args->content, "-") == 0))
	{
		while ((*ghost)->env[i])
		{
			if (ft_strnstr((*ghost)->env[i], "HOME", ft_strlen("HOME")) 
				!= 0 && (ft_strcmp(cmd->args->content, "~") == 0))
			{
				if (chdir(&(*ghost)->env[i][5]) != 0)
					strerror(errno);
			}
			// if (ft_strnstr((*ghost)->env[i], "OLDPWD", ft_strlen("OLDPWD"))
			// 	!= 0 && (ft_strcmp(cmd->args->content, "-") == 0))
			// {
			// 	if (chdir(&(*ghost)->env[i][7]) != 0)
			// 		strerror(errno);
			// }
			i++;
		}
	}
	// else if (ft_strcmp(cmd->args->content, "-") == 0)
	// {
	// 	while ((*ghost)->env[i])
	// 	{
	// 		if (ft_strnstr((*ghost)->env[i], "OLDPWD", ft_strlen("OLDPWD")) != 0)
	// 		{
	// 			if (chdir(&(*ghost)->env[i][7]) != 0)
	// 				strerror(errno);
	// 		}
	// 		i++;
	// 	}
	// }
	else
	{
		if (chdir(cmd->args->content) != 0)
			strerror(errno);
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
	int i = 0;


	if (cmd->args != NULL)
		return (1);
	while ((*ghost)->env[i])
	{
		ft_putstr_fd((*ghost)->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (1);
}

int	export_replace(char *str, t_shell **ghost)
{
	int i;
	char *var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			var = (char*)malloc(sizeof(char) * (i + 1));
			ft_strlcpy(var, str, i + 1);
			i = 0;
			break;
		}
		i++;
	}
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], var, ft_strlen(var)))
		{
			free((*ghost)->env[i]);
			(*ghost)->env[i] = ft_strdup(str);
			free(var);
			return (0);
		}
		i++;
	}
	free(var);
	return (1);
}

int	run_export(t_cmd *cmd, t_shell **ghost)
{
	int i;
	char *str;

	i = 0;
	str = cmd->args->content;
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && (str[i] != '_' && str[i] != '$'
			&& str[i] != '=' && str[i] != '/' && str[i] != '"')) || str[0] == '=')
		{
			cmd_notfound(cmd, EXPRT_FAIL, ghost, 0);
			return (1);
		}
		i++;
	}
	if (!cmd->args)
		return (1);
	if (export_replace(str, ghost))
		(*ghost)->env = arr_addback((*ghost)->env, cmd->args->content);
	return (1);
}

int	run_unset(t_cmd *cmd, t_shell **ghost)
{
	int i;
	int k = 0;

	i = 0;
	if (!cmd->args)
		return (1);
	int len = ft_strlen(cmd->args->content);
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], cmd->args->content, len))
			k = i;
		i++;
	}
	char **temp;
	temp = (char**)malloc(sizeof(char*) * (i));
	int j = 0;
	for (int i = 0; (*ghost)->env[i]; i++)
	{
		if (i != k)
		{
			temp[j] = (*ghost)->env[i];
			j++;
		}
		else
			free((*ghost)->env[i]);
	}
	temp[j] = 0;
	free((*ghost)->env);
	(*ghost)->env = (char**)malloc(sizeof(*temp));
	(*ghost)->env = temp;
	return(1);
}

int	run_exit(t_cmd *cmd, t_shell **ghost)
{
	char *exit_code;

	// ft_putnbr_fd((*ghost)->pid, 1);
	if ((*ghost)->pid != 0 && cmd->seprator_type != PIPE)
	{
		ft_putstr_fd("exit", 1);
		ft_putstr_fd("\n", 1);
		// free_all(ghost);
	}
	// system("leaks ghostshell");
	if (!cmd->args)
		exit(0);
	else
	{
		exit_code = cmd->args->content;
		if (ft_isdigit(exit_code[0])) // Need to perfect this tbh
		{
			exit(ft_atoi(exit_code));
		}
		else
		{
			ft_putstr_fd("ghostshell: ", 1);
			ft_putstr_fd(exit_code, 1);
			ft_putstr_fd(": numeric argument reguired\n", 1);
			exit(0);
		}
	}
	(void)ghost;
	// system ("leaks ghostshell");
}

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
			if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			{
				if (cmd->redirection)
					(*ghost)->out = redirect(cmd, ghost);
				if ((*ghost)->out == -1)
					return(1);
				(*g_builtin_f[i])(cmd, ghost);
				if ((*ghost)->out != -42)
				{
					// if ((*ghost)->out == 0)
					// 	dup2((*ghost)->out, STDIN_FILENO);
					// else
					dup2((*ghost)->out, STDOUT_FILENO);
					// ft_putstr_fd("In here?", 1);
				}
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
		{
			// if ((*ghost)->out == 0)
			// 	dup2((*ghost)->out, STDIN_FILENO);
			// else
			dup2((*ghost)->out, STDOUT_FILENO);
			// ft_putstr_fd("In here?", 1);
		}
		if (!command->next)
		{
			if ((*ghost)->pipefd[0] != -69)
				close((*ghost)->pipefd[0]);
			return (1);
		}
	}
	return (1);
}
