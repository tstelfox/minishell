/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/06 13:00:59 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_dir(t_cmd *cmd, t_shell **ghost)
{
	struct stat buf;

	lstat(cmd->type, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		(*ghost)->error = DIRECTORY;
		return(0);
	}
	return (1);
}

char	**get_path(t_cmd *cmd, t_shell **ghost)
{
	int i;
	int k;
	char **path;
	char *command;

	i = 0;
	k = 0;
	command = ft_strjoin("/", cmd->type);
	if ((*ghost)->path != 0)
	{
		for (int i = 0; (*ghost)->path[i]; i++)
			free((*ghost)->path[i]);
		free((*ghost)->path);
	}
	while ((*ghost)->env[i])
	{
		if (ft_strnstr((*ghost)->env[i], "PATH", 4))
		{
			path = ft_split(&(*ghost)->env[i][5], ':');
			while (path[k])
			{
				path[k] = ft_strjoinfree(path[k], command);
				k++;
			}
			free(command);
			return(path);
		}
		i++;
	}
	return (0);
}

void	path_launch(t_cmd *cmd, t_shell **ghost)
{
	if (!check_dir(cmd, ghost))
	{
		cmd_notfound(cmd, (*ghost)->error, ghost, 0);
		return ;
	}
	if (cmd->type[0] == '.' && cmd->type[1] == '/')
	{
		char **args;
		if (cmd->args)
		{
			t_list	*fucker = ft_lstnew(ft_strdup(cmd->type));
			ft_lstadd_front(&cmd->args, fucker);
			args = list_to_arr(cmd->args);
		}
		else
		{
			args = (char**)malloc(sizeof(char *) * 2);
			args[0] = ft_strdup(cmd->type);
			args[1] = NULL;
		}
		execve(cmd->type, args, (*ghost)->env);
		cmd_notfound(cmd, 0, ghost, 0);
	}
}

int	prog_launch(t_cmd *cmd, t_shell **ghost)
{
	// char **path;
	char **args;
	int	w_status;

	int k = 0;
	(*ghost)->path = get_path(cmd, ghost);
	if ((*ghost)->path == NULL)
	{
		cmd_notfound(cmd, (*ghost)->error, ghost, 0); // Might need some work
		// ft_putnbr_fd((*ghost)->error, 1);
	}
	int i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			return(1);
		i++;
	}
	if (cmd->args)
	{
		t_list	*fucker = ft_lstnew(ft_strdup(cmd->type));
		ft_lstadd_front(&cmd->args, fucker);
		args = list_to_arr(cmd->args);
	}
	else
	{
		args = (char**)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(cmd->type);
		args[1] = NULL;
	}
	(*ghost)->pid = fork();
	signal(SIGINT, ctrl_process);
	signal(SIGQUIT, ctrl_process);
	if ((*ghost)->pid == 0) //child process
	{
		if (cmd->redirection)
		{
			if (redirect(cmd, ghost) == -1)
				exit(1);
		}
		if (ft_strchr(cmd->type, '/'))
		{
			path_launch(cmd, ghost);
			if ((*ghost)->error == DIRECTORY || errno == EACCES)
				exit(126);
			exit(127);
		}
		else
		{
			while ((*ghost)->path[k])
			{
				if (execve((*ghost)->path[k], args, (*ghost)->env) == -1)
					(*ghost)->ret_stat = 1;
				k++;
			}
			cmd_notfound(cmd, 0, ghost, 0);
			exit(127);
		}
	}
	else if ((*ghost)->pid < 0)
		strerror(errno);
	else
	{
		waitpid((*ghost)->pid, &w_status, WUNTRACED);
		// signal(SIGINT, ctrl_process);
		for (int i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		if (WIFSIGNALED(w_status))
			(*ghost)->ret_stat = WTERMSIG(w_status);
		if (WIFEXITED(w_status))
			(*ghost)->ret_stat = WEXITSTATUS(w_status);
	}
	return (1);
}
