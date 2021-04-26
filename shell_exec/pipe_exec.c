/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:07:07 by tmullan       #+#    #+#                 */
/*   Updated: 2021/04/26 17:49:12 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	pipe_prog(t_cmd *cmd, t_shell **ghost)
{
	char **path;
	char **args;
	int k;

	path = get_path(cmd, ghost);
	if (path == NULL)
		cmd_notfound(cmd, (*ghost)->error, ghost, ERR_PIPE); // This might need some work. maybe exit
	k = 0;
	if (cmd->args)
	{
		t_list *prog = ft_lstnew(ft_strdup(cmd->type));
		ft_lstadd_front(&cmd->args, prog);
		args = list_to_arr(cmd->args);
	}
	else
	{
		args = (char**)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(cmd->type);
		args[1] = NULL;
	}
	// close(fd_in);
	while (path[k])
	{
		if (execve(path[k], args, NULL) == -1)
		{
			// ft_putnbr_fd(errno, 1);
			(*ghost)->ret_stat = 1;
		}
		k++;
	}
	// close((*ghost)->pipefd[0]);
	// pipe_err_message(cmd, ghost)
	cmd_notfound(cmd, 0, ghost, ERR_PIPE);
	exit(0);
}

int		first_cmd(pid_t pid, t_list *command, t_shell **ghost, int fd_in)
{
	int i;
	t_cmd *cmd;
	int w_status;

	i = 0;
	cmd = command->content;
	// if (fd_in != 0)
	// 	close(fd_in);
	if (pid == 0)
	{
		if (cmd->redirection) // Here goes nothing
			(*ghost)->out = redirect(cmd, ghost);
		dup2(fd_in, 0);
		(*ghost)->out_pipe = dup(STDOUT_FILENO);
		if (command->next != NULL && !cmd->redirection)
			dup2((*ghost)->pipefd[1], STDOUT_FILENO);
		close((*ghost)->pipefd[0]);
		while (i < 7)
		{
			if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			{
				(*g_builtin_f[i])(cmd, ghost);
				// close(fd_in);
				exit(0);
			}
			i++;
		}
		pipe_prog(cmd, ghost);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		waitpid(pid, &w_status, WUNTRACED);
		if (WIFEXITED(w_status))
			(*ghost)->ret_stat = WEXITSTATUS(w_status);
		else if (WIFSIGNALED(w_status))
			(*ghost)->ret_stat = WTERMSIG(w_status);
		close((*ghost)->pipefd[1]);
		// close((*ghost)->pipefd[0]);
		// close(fd_in);
		fd_in = (*ghost)->pipefd[0];
	}
	return (fd_in);
}

int		pipe_exec(t_list *command, t_shell **ghost)
{
	int		fd_in;
	// int		pipe_old[2];

	fd_in = 0;
	// // Execute first in a fork()
	while (command)
	{
		// if ((*ghost)->pipefd[0] != -69)
		// {
		// 	pipe_old[0] = (*ghost)->pipefd[0];
		// 	pipe_old[1] = (*ghost)->pipefd[1];
		// 	close(pipe_old[0]);
		// 	close(pipe_old[1]);
		// }
		// if ((*ghost)->pipefd[1] != -47)
		// 	close((*ghost)->pipefd[1]);
		pipe((*ghost)->pipefd);
		(*ghost)->pid = fork();
		fd_in = first_cmd((*ghost)->pid, command, ghost, fd_in);
		command = command->next;
	}
	// // Close write pipe
	// close(ghost->pipefd[1]);
	// dup2(ghost->pipefd[0], STDIN_FILENO);
	
	// // Execute second command (Always in a fork or only for exec?)

	// // Return to main loop
	return (1);
}
