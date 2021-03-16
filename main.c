/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/16 13:35:35 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ctrl(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b \b", 1);
		ft_putstr_fd("\b \b", 1);
		ft_putstr_fd("\n\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b \b", 1);
		ft_putstr_fd("\b \b", 1);
	}
}

void	exec_shell(char *envp[])
{
	char	*input;
	t_shell *ghost;

	ghost = init_shell(envp);
	if (!ghost)
		error_handler(&ghost, INTERNAL_ERROR, "could not allocate space", NULL);

	// ---------env---------
	int i = 0;
	while (envp[i])
		i++;
	ghost->env = (char **)malloc(sizeof(char *) * (i + 1));
	int k = 0;
	while (envp[k])
	{
		ghost->env[k] = ft_strdup(envp[k]);
		k++;
	}
	ghost->env[k] = 0;
	// ---------env---------

	signal(SIGINT, ctrl);
	// signal(SIGQUIT, ctrl); // I need this to be able to quite sometimes lol

	input = NULL;
	while (ghost->status != INTERNAL_ERROR) // check for errors
	{
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
		read_line(&input);

		lexer(&ghost, input);
		if (ghost->status == 0)
			parser(&ghost);
		if (shell_exec(ghost->commands, ghost) == 0)
			break;
		if (ghost->status == 0)// debug
		{
			ft_lstiter(ghost->tokens, print_data);
			ft_putstr_fd("\n", STDOUT_FILENO);
			ft_cmd_lstiter(ghost->commands, print_cmd);
		}
		else//if error debug
		{
			ft_putnbr_fd(ghost->status, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		free(input);
		restart_shell(ghost);
	}
}

int	main(int argc, char *args[], char *envp[])
{
	(void)argc;
	(void)args;

	exec_shell(envp);
	return (0);
}
