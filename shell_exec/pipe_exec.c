/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:07:07 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/22 13:09:52 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int		pipe_redirect(void)
{
	int	out;

	out = dup(STDOUT_FILENO);
	dup2(STDIN_FILENO, STDOUT_FILENO);
	return (out);
}

// int		first_cmd(pid_t pid, t_cmd *cmd, t_shell *ghost)
// {
// 	if (pid == 0)
// 	{
		
// 	}
// }

int		pipe_exec(t_list *commands, t_shell *ghost)
{
	// Redirect stdout to stdin
	t_cmd	*cmd;
	// pid_t	pid;
	// int		stdout;

	cmd = (t_cmd*)commands->content;
	(void)ghost;
	// stdout = pipe_redirect(void);

	// // Execute first in a fork()
	// pid = fork();
	// if (!first_cmd(pid, cmd, ghost))
	// {
	// 	cmd_notfound(cmd);
	// 	exit(0);
	// }
	// // print stdin to check what's there

	// // Redirect stdout back to stdout

	// // Execute second command (Always in a fork or only for exec?)

	// // Return to main loop
	return (47);
}
