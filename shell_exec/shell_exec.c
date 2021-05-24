/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_exec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/16 13:33:57 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/24 15:54:10 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	pipe_or_next(t_list *command, t_shell **ghost, t_cmd *cmd, int i)
{
	if (cmd->seprator_type == PIPE)
	{
		pipe_exec(command, ghost);
		return (1);
	}
	if (i != 0)
	{
		i = 0;
		command = command->next;
		cmd = command->content;
	}
	return (i);
}

int	launch_built_in(t_list *command, t_shell **ghost, t_cmd *cmd, int i)
{
	while (i < 7)
	{
		if (redirection_handle(ghost, cmd))
			return (1);
		if (ft_strcmp(cmd->type, (*ghost)->built_in[i]) == 0)
		{
			if ((*ghost)->in != -42)
				dup2((*ghost)->in, STDIN_FILENO);
			(*ghost)->ret_stat = 0;
			(*ghost)->g_builtin_f[i](cmd, ghost);
			if ((*ghost)->out != -42)
				dup2((*ghost)->out, STDOUT_FILENO);
			if (!command->next)
			{
				if ((*ghost)->pipefd[0] != -69)
					close((*ghost)->pipefd[0]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	shell_exec(t_list *command, t_shell **ghost)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	if (command->content == NULL)
		return (0);
	cmd = command->content;
	while (1)
	{
		i = pipe_or_next(command, ghost, cmd, i);
		if (i == 1)
			return (1);
		if (launch_built_in(command, ghost, cmd, i))
			return (1);
		prog_launch(cmd, ghost);
		if ((*ghost)->out != -42)
			dup2((*ghost)->out, STDOUT_FILENO);
		if (!command->next)
		{
			if ((*ghost)->pipefd[0] != -69)
				close((*ghost)->pipefd[0]);
			return (1);
		}
	}
	return (1);
}
