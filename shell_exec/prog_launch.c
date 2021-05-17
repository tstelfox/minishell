/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/17 17:03:29 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	check_dir(t_cmd *cmd, t_shell **ghost)
{
	struct stat	buf;

	lstat(cmd->type, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		(*ghost)->error = DIRECTORY;
		return (0);
	}
	return (1);
}

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr != 0)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

char	**get_path(t_cmd *cmd, t_shell **ghost)
{
	int		i;
	int		k;
	char	**path;
	char	*command;

	i = 0;
	k = 0;
	command = ft_strjoin("/", cmd->type);
	free_arr((*ghost)->path);
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
			return (path);
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
	execve(cmd->type, (*ghost)->args, (*ghost)->env);
	cmd_notfound(cmd, 0, ghost, 0);
}

void	get_args(t_cmd *cmd, t_shell **ghost)
{
	t_list	*command;

	free_arr((*ghost)->args);
	command = ft_lstnew(ft_strdup(cmd->type));
	if (cmd->args)
	{
		ft_lstadd_front(&cmd->args, command);
		(*ghost)->args = list_to_arr(cmd->args);
	}
	else
	{
		(*ghost)->args = list_to_arr(command);
		free(command->content);
		free(command);
	}
}

void	prog_child(t_cmd *cmd, t_shell **ghost)
{
	int	k;

	k = 0;
	if (cmd->redirection && redirect(cmd, ghost) == -1)
		exit(1);
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
			if (execve((*ghost)->path[k], (*ghost)->args, (*ghost)->env) == -1)
				(*ghost)->ret_stat = 1;
			k++;
		}
		cmd_notfound(cmd, 0, ghost, 0);
		exit(127);
	}
}

int	prog_launch(t_cmd *cmd, t_shell **ghost)
{
	int		w_status;

	(*ghost)->path = get_path(cmd, ghost);
	if ((*ghost)->path == NULL)
		cmd_notfound(cmd, (*ghost)->error, ghost, 0);
	get_args(cmd, ghost);
	(*ghost)->pid = fork();
	signal(SIGINT, ctrl_process);
	signal(SIGQUIT, ctrl_process);
	if ((*ghost)->pid == 0)
		prog_child(cmd, ghost);
	else if ((*ghost)->pid < 0)
		strerror(errno);
	else
	{
		waitpid((*ghost)->pid, &w_status, WUNTRACED);
		if (WIFSIGNALED(w_status))
			(*ghost)->ret_stat = WTERMSIG(w_status);
		if (WIFEXITED(w_status))
			(*ghost)->ret_stat = WEXITSTATUS(w_status);
	}
	return (1);
}
