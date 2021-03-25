/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:07:07 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/25 15:57:09 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

// int		pipe_redirect(void)
// {
// 	int	out;

// 	out = dup(STDOUT_FILENO);
// 	dup2(STDIN_FILENO, STDOUT_FILENO);
// 	return (out);
// }

void	pipe_prog(t_cmd *cmd, t_shell *ghost)
{
	char **path;
	char **args;
	int k;

	path = get_path(cmd, ghost);
	if (path == NULL)
		cmd_notfound(cmd, ghost->error); // This might need some work. maybe exit
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
	while (path[k])
	{
		if (execve(path[k], args, NULL) == -1)
			strerror(errno);
		k++;
	}
	cmd_notfound(cmd, 0);
	exit(0);
}

int		first_cmd(pid_t pid, t_list *command, t_shell *ghost, int fd_in)
{
	int i;
	t_cmd *cmd;

	i = 0;
	cmd = command->content;
	if (pid == 0)
	{
		dup2(fd_in, 0);
		if (command->next != NULL)
			dup2(ghost->pipefd[1], STDOUT_FILENO);
		close(ghost->pipefd[0]);
		while (i < 7)
		{
			if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			{
				(*g_builtin_f[i])(cmd, ghost);
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
		waitpid(pid, &ghost->status, 0);
		close(ghost->pipefd[1]);
		fd_in = ghost->pipefd[0];
	}
	return (fd_in);
}

int		pipe_exec(t_list *command, t_shell *ghost)
{
	pid_t	pid;
	int		fd_in;

	fd_in = 0;
	// // Execute first in a fork()
	while (command)
	{
		pipe(ghost->pipefd);
		pid = fork();
		fd_in = first_cmd(pid, command, ghost, fd_in);
		command = command->next;
	}
	// // Close write pipe
	// close(ghost->pipefd[1]);
	// dup2(ghost->pipefd[0], STDIN_FILENO);
	
	// // Execute second command (Always in a fork or only for exec?)

	// // Return to main loop
	return (1);
}
