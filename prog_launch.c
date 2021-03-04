/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/04 13:02:34 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	prog_launch(t_list *tokens, t_shell *ghost)
{
	pid_t	pid;
	(void)tokens;
	(void)ghost;
	int		status;
	char	command[11] = "/bin/ls";
	char	*args[2] = { "ls", NULL};
	
	// command = "/bin/ls";
	// ft_putstr_fd(command, 1);
	// tokens = tokens->next;
	// tokens = tokens->next;
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
		ft_putstr_fd("In hereeeee?", 1);
	}
	else
	{
		// ft_putstr_fd("porcoddio", 1);
		waitpid(pid, &status, 0);
		// printf("%d\n", pid);
		if (WIFSIGNALED(status)) {
        	ft_putstr_fd("Error\n", 1);
    	}
    	else if (WEXITSTATUS(status)) {
       		// ft_putstr_fd("Exited Normally\n", 1);
    	}
	}
	return (1);
}