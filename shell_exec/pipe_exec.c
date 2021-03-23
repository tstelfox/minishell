/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_exec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 14:07:07 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/23 10:54:33 by tmullan       ########   odam.nl         */
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

void	pipe_prog(t_cmd *cmd, t_shell *ghost)
{
	char **path;
	char **args;
	int k;

	path = get_path(cmd, ghost);
	if (path == NULL)
		cmd_notfound(cmd); // This might need some work. maybe exit
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
	cmd_notfound(cmd);
	exit(0);
}

int		first_cmd(pid_t pid, t_cmd *cmd, t_shell *ghost)
{
	int i;

	i = 0;
	if (pid == 0)
	{
		ft_putstr_fd("HELLO?", 1);
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
		waitpid(pid, &ghost->status, 0);
	return (1);
}

int		pipe_exec(t_list *commands, t_shell *ghost)
{
	// Redirect stdout to stdin
	t_cmd	*cmd;
	pid_t	pid;
	int		stdout;

	cmd = (t_cmd*)commands->content;
	// (void)ghost;
	stdout = pipe_redirect();

	// // Execute first in a fork()
	pid = fork();
	first_cmd(pid, cmd, ghost);
	// // Redirect stdout back to stdout
	dup2(stdout, STDOUT_FILENO);
	// // print stdin to check what's there
	// char line[1000];
	// fgets(line, 1000, STDIN_FILENO);
	// ft_putstr_fd("ere\n", STDOUT_FILENO);
	// ft_putstr_fd(line, STDOUT_FILENO);
	

	// // Execute second command (Always in a fork or only for exec?)

	// // Return to main loop
	return (1);
}
