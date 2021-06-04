/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmullan <tmullan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 17:15:49 by tmullan       #+#    #+#                 */
/*   Updated: 2021/06/03 11:52:39 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

int	parse_exit(t_cmd *cmd, t_shell **ghost, char *exit_code, int i)
{
	while (exit_code[i])
	{
		if (!ft_isdigit(exit_code[i]) && exit_code[i] != '-')
			break ;
		if (i != 0 && !ft_isdigit(exit_code[i]))
			break ;
		if (cmd->args->next)
		{
			cmd_notfound(cmd, TOO_MANY_ARGS, ghost, 0);
			(*ghost)->ret_stat = 1;
			return (1);
		}
		i++;
		if (!exit_code[i])
		{
			i = ft_atoi(exit_code);
			while (i > 255)
				i -= 256;
			while (i < 0)
				i += 256;
			exit(i);
		}
	}
	return (0);
}

int	run_exit(t_cmd *cmd, t_shell **ghost)
{
	char	*exit_code;
	t_list	*commands;
	t_cmd	*first_cmd;
	int		i;

	i = 0;
	commands = (*ghost)->commands;
	first_cmd = commands->content;
	if (first_cmd->seprator_type != PIPE)
		ft_putstr_fd("exit\n", 1);
	if (!cmd->args)
		exit(0);
	else
	{
		exit_code = cmd->args->content;
		if (parse_exit(cmd, ghost, exit_code, i) == 1)
			return (1);
		cmd_notfound(cmd, BAD_ARG_EXIT, ghost, 0);
		exit(255);
	}
}
