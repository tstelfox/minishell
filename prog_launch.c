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

int	prog_launch(t_list *tokens, t_shell *ghost)
{
	pid_t	pid;
	(void)ghost;
	int		status; //Ok need to put list in 2D array and then do a strjoin
	char	command[11] = "/bin/ls";
	char	*args[3] = { "ls", NULL};
	pid = fork();
	if (pid == 0) //child process
	{
		if (execve(command, args, NULL) == -1)
		{
			printf("%s: errno %d\n", strerror(errno), errno);
		}
		ft_putstr_fd("ghostshell: ", 1);
		ft_putstr_fd(tokens->content, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(0);
	}
	else if (pid < 0)
	{
		strerror(errno);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (1);
}