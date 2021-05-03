/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/03 16:34:41 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		check_dir(t_cmd *cmd, t_shell **ghost)
{
	struct stat buf;
	// int		fd;

	lstat(cmd->type, &buf);
	// ft_putstr_fd("ma porcoddio \n", 1);
	// ft_putstr_fd(strerror(errno), 1);
	if (S_ISDIR(buf.st_mode))
	{
		// ft_putstr_fd("ma porcoddio cane \n", 1);
	// 	ft_putstr_fd("ghostshell: ", 1);
	// 	ft_putstr_fd(cmd->type, 1);
	// 	ft_putstr_fd(": is a directory\n", 1);
		(*ghost)->error = DIRECTORY;
		return(0);
	}
	// else
	// {
	// 	fd = open(cmd->type, O_TRUNC);
	// 	// ft_putnbr_fd(fd, 1);
	// 	if (fd == -1)
	// 	{
	// 		ft_putstr_fd("ma porcoddio \n", 1);
	// 		(*ghost)->error = NO_ACCESS;
	// 		return(0);
	// 	}
	// 	else
	// 		close(fd);
	// }
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
			// path = arr_addback(path, cmd->type);
			// (*ghost)->path = (char**)malloc(sizeof(char *) * (k + 1));
			free(command);
			return(path);
		}
		i++;
	}
	// free(command);
	// cmd_notfound(cmd, (*ghost)->error, ghost, 0);
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
		// exit(127);
		// path = (char**)malloc(sizeof(char*) * 2);
		// path[0] = ft_strdup(cmd->type);
		// path[1] = NULL;
		// if ((*ghost)->error != DIRECTORY)
		// 	(*ghost)->error = NO_ACCESS; // This needs to catch properly
		// if (execve(cmd->type, args, NULL) == -1)
		// 	(*ghost)->error = NO_ACCESS;
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
	// else
	// 	args = NULL;
	(*ghost)->pid = fork();
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
				if (execve((*ghost)->path[k], args, NULL) == -1)
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
