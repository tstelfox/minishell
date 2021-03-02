/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/02 17:15:09 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	prog_launch(t_list *tokens, t_shell *ghost)
{
	pid_t	pid;
	char	*command;
	
	command = tokens->content;
	tokens = tokens->next;
	tokens = tokens->next;
	pid = fork();
	if (pid == 0) //child process
	{
		if (execve(command, tokens->content, ghost->env) == -1)
			strerror(errno);
		exit(0);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		waitpid(pid, &ghost->status, -1);
	}
	ft_putstr_fd("ghostshell: ", 1);
	ft_putstr_fd(tokens->content, 1);
	ft_putstr_fd(": command not found\n", 1);
	return (1);
}