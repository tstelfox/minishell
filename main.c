/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/17 16:30:41 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void print_env(char **str)
{
	while (*str)
	{
		printf("[%s]\n", *str);
		str++;
	}
}

void	ctrl(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n\e[1;34mghostshell$> \e[0m", STDERR_FILENO);
}

void	ctrl_process(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}

void	exec_shell(char *envp[])
{
	t_shell	*ghost;
	t_list	*head;
	char	*line;

	ghost = init_shell(envp);
	if (!ghost)
		error_handler(&ghost, INIT_ERROR, "failed to initialize structs", NULL);
	init_reins(&ghost);
	while (ghost->status != INTERNAL_ERROR) // check for errors
	{
		signal(SIGINT, ctrl);
		signal(SIGQUIT, SIG_IGN);
		// print_env(ghost->env);
		ghost->first_command = TRUE;// for storing the first command in history;
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDERR_FILENO);
		line = read_line(&ghost);
		// printf("BEFO\n");
		ghost->tokens = lexer(&ghost, line, " ><|;");
		// ft_lstiter(ghost->tokens, print_data);
		// ft_putstr_fd("\n", STDOUT_FILENO);
		head = ghost->tokens;
		free(line);
		while (ghost->tokens)
		{
			ghost->commands = parser(&ghost);
			// ft_cmd_lstiter(ghost->commands, print_cmd);
			if (!ghost->commands)
				break ;
			// printf("LOOOOOOL\n");
			if (ghost->commands && !ghost->error)
				if (shell_exec(ghost->commands, &ghost) == 0)
					return ;
			ghost->error = 0;
			// if (ghost->commands)
			// {
			// 	printf("DEUG\n");
			// 	ft_lstclear(&ghost->commands, del_commands);
			// 	free(ghost->commands);
			// }
			// // free(ghost->commands);
		}
		ghost->tokens = head;
		// ft_lstiter(ghost->tokens, print_data);
		restart_shell(&ghost);
		// printf("RESET\n");
	}
	reins_destroy(ghost->reins);
}

int	main(int argc, char *args[], char *envp[])
{
	(void)argc;
	(void)args;
	exec_shell(envp);
	// test();
	// (void)envp;
	return (0);
}
