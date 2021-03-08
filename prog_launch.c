/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/04 13:22:16 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	prog_launch(t_cmd *cmd, t_shell *ghost)
{
	pid_t	pid;
	char *command;

	command = ft_strjoin("/bin/", cmd->type);
	char **args;

	int i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->type, g_builtin[i]) == 0)
			return(1);
		i++;
	}

	if (cmd->args)
	{
		t_list	*fucker = ft_lstnew(cmd->type);
		ft_lstadd_front(&cmd->args, fucker);
		args = list_to_arr(cmd->args);
	}
	else
	{
		args = (char**)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(cmd->type);
		args[1] = NULL;
	}
	pid = fork();
	if (pid == 0) //child process
	{
		if (execve(command, args, NULL) == -1)
		{
			(void)pid;
			// printf("%s: errno %d\n", strerror(errno), errno);
		}
		ft_putstr_fd("ghostshell: ", 1);
		ft_putstr_fd(cmd->type, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(0);
	}
	else if (pid < 0)
	{
		strerror(errno);
	}
	else
	{
		waitpid(pid, &ghost->status, 0);
	}
	return (1);
}