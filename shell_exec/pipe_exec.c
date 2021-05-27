/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:07:07 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/27 12:59:30 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	pipe_prog(t_cmd *cmd, t_shell **ghost)
{
	int		k;

	(*ghost)->path = get_path(cmd, ghost);
	if ((*ghost)->path == NULL)
		cmd_notfound(cmd, (*ghost)->error, ghost, 0);
	k = 0;
	get_args(cmd, ghost);
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
	}
	cmd_notfound(cmd, 0, ghost, 0);
	exit(127);
}

void	pipe_child(t_list *command, t_shell **ghost)
{
	int		i;
	t_cmd	*cmd;	

	i = 0;
	cmd = command->content;
	(*ghost)->out_pipe = dup(STDOUT_FILENO);
	if (command->next != NULL)
	{
		dup2((*ghost)->pipefd[1], STDOUT_FILENO);
		close((*ghost)->pipefd[1]);
	}
	close((*ghost)->pipefd[0]);
	if (cmd->redirection)
		(*ghost)->out = redirect(cmd, ghost);
	while (i < 7)
	{
		if (ft_strcmp(cmd->type, (*ghost)->built_in[i]) == 0)
		{
			(*ghost)->g_builtin_f[i](cmd, ghost);
			exit(0);
		}
		i++;
	}
	pipe_prog(cmd, ghost);
}

void	pipe_parent(t_list *command, t_shell **ghost, int w_status)
{
	if (!command->next)
	{
		waitpid((*ghost)->pid, &w_status, WUNTRACED);
		close((*ghost)->pipefd[0]);
		if (WIFEXITED(w_status))
			(*ghost)->ret_stat = WEXITSTATUS(w_status);
		else if (WIFSIGNALED(w_status))
			(*ghost)->ret_stat = WTERMSIG(w_status);
	}
	close((*ghost)->pipefd[1]);
}

int	pipe_loop(t_list *command, t_shell **ghost, int fd_in, int num)
{
	t_cmd	*cmd;
	int		w_status;

	w_status = 0;
	cmd = command->content;
	if ((*ghost)->pid == 0)
	{
		if (num != 0)
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
		pipe_child(command, ghost);
	}
	else if ((*ghost)->pid < 0)
		strerror(errno);
	else
	{
		pipe_parent(command, ghost, w_status);
		if (num != 0)
			close(fd_in);
		fd_in = (*ghost)->pipefd[0];
	}
	return (fd_in);
}

int	pipe_exec(t_list *command, t_shell **ghost)
{
	int		fd_in;
	int		i;

	fd_in = 0;
	i = 0;
	while (command)
	{
		pipe((*ghost)->pipefd);
		(*ghost)->pid = fork();
		signal(SIGINT, ctrl_process);
		signal(SIGQUIT, ctrl_process);
		fd_in = pipe_loop(command, ghost, fd_in, i);
		command = command->next;
		i++;
	}
	return (1);
}
