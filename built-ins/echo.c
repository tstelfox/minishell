/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/22 12:47:23 by tmullan       #+#    #+#                 */
/*   Updated: 2021/05/22 12:47:42 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_echo(t_list *args)
{
	while (args->next)
	{
		ft_putstr_fd(args->content, STDOUT_FILENO);
		ft_putstr_fd(" ", 1);
		args = args->next;
	}
	ft_putstr_fd(args->content, STDOUT_FILENO);
}

int	run_echo(t_cmd *cmd, t_shell **ghost)
{
	t_list	*head;

	(void)ghost;
	if (cmd->args == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	head = cmd->args;
	if (ft_strcmp(cmd->args->content, "-n") == 0)
	{
		cmd->args = cmd->args->next;
		print_echo(cmd->args);
	}
	else
	{
		print_echo(cmd->args);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	cmd->args = head;
	return (1);
}
