/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prog_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 16:29:22 by tmullan       #+#    #+#                 */
/*   Updated: 2021/03/09 17:37:20 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

char	**get_path(t_cmd *cmd, t_shell *ghost)
{
	int i;
	int k;
	char **path;
	char *command;

	i = 0;
	k = 0;
	command = ft_strjoin("/", cmd->type);
	while (ghost->env[i])
	{
		if (ft_strnstr(ghost->env[i], "PATH", 4))
		{
			path = ft_split(&ghost->env[i][5], ':');
			while (path[k])
			{
				path[k] = ft_strjoin(path[k], command);
				k++;
			}
			return(path);
		}
		i++;
	}
	return (0);
}

int	prog_launch(t_cmd *cmd, t_shell *ghost)
{
	pid_t	pid;
	char **path;
	char **args;
	int k = 0;

	path = get_path(cmd, ghost);
	if (path == NULL)
		cmd_notfound(cmd);
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
	else if (cmd->redirection) // This shit is all krfucked
	{
		t_list	*tuma = ft_lstnew(cmd->type);
		t_list	*symbol = ft_lstnew(">");
		t_list  *file = ft_lstnew("test");
		// t_list  *file = ft_lstnew(cmd->redirection->content->file);
		ft_lstadd_back(&tuma, symbol);
		ft_lstadd_back(&tuma, file);
		args = list_to_arr(tuma);
	}
	else
	{
		args = (char**)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(cmd->type);
		args[1] = NULL;
	}
	// for (int i = 0; args[i]; i++)
	// {
	// 	ft_putstr_fd(args[i], 1);
	// 	ft_putstr_fd("\n", 1);
	// }
	pid = fork();
	if (pid == 0) //child process
	{
		while (path[k])
		{
			if (execve(path[k], args, NULL) == -1)
			{
				(void)pid;
				// printf("%s: errno %d\n", strerror(errno), errno);
			}
			k++;
		}
		cmd_notfound(cmd);
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
