/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/08 18:12:21 by ztan          ########   odam.nl         */
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
		ft_putstr_fd("exit", 0);
	}
	// signal(SIGINT, ctrl);
}

void	exec_shell(char *envp[])
{
	char	*input;
	t_shell *ghost;

	ghost = init_shell(envp);
	if (!ghost)
		error_handler(&ghost, INTERNAL_ERROR, "could not allocate space", NULL);
	// pid_t	pid;
	// int		status;
	signal(SIGINT, ctrl);
	signal(SIGQUIT, ctrl);

	input = NULL;
	while (ghost->status != INTERNAL_ERROR) // check for errors
	{
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
		read_line(&input);

		lexer(&ghost, input);
		if (ghost->status == 0)
			parser(&ghost);
		if (ghost->status == 0)// debug
		{
			ft_lstiter(ghost->tokens, print_data);
			ft_putstr_fd("\n", STDOUT_FILENO);
			ft_cmd_lstiter(ghost->commands, print_cmd);
		}
		else
		{
			ft_putnbr_fd(ghost->status, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		// if (builtin_exec(tokens, &ghost) == 0) //Presuming that the input has been processed
		// 	break;
		// pid = fork();

		// if (pid == 0)
		// {
		// 	if (execvp(tokens->content, tokens) == -1)
		// 	{
		// 		strerror(errno);
		// 		exit(1);
		// 	}
		// }
		// else
		// 	waitpid(pid, &status, 0);
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
