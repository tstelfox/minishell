/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/04/26 10:29:55 by ztan          ########   odam.nl         */
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
	{
		ft_putstr_fd("\b \b", 1);
		ft_putstr_fd("\b \b", 1);
		ft_putstr_fd("\n\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
	}
	if (sig == SIGQUIT)
	{
		// ft_putstr_fd("\b \b", 1);
		// ft_putstr_fd("\b \b", 1);
	}
}

void	exec_shell(char *envp[])
{
	t_shell *ghost;
	t_list *head;

	ghost = init_shell(envp);
	if (!ghost)
		error_handler(&ghost, INIT_ERROR, "failed to initialize structs", NULL);
	init_reins(&ghost);
	signal(SIGINT, ctrl);
	signal(SIGQUIT, ctrl); // I need this to be able to quite sometimes lol
	while (ghost->status != INTERNAL_ERROR) // check for errors
	{
		head = ghost->tokens;
		// print_env(ghost->env);
		ghost->first_command = TRUE;// for storing the first command in history;
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
		read_line(&ghost);
		ghost->tokens = lexer(&ghost, ghost->line, " ><|;");
		// ft_lstiter(ghost->tokens, print_data);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		// printf("\nDEBUG_AFTER\n");
		while (ghost->status != FINISHED)
		{
			// printf("DEBUG\n");
			parser(&ghost);
			// printf("DEBUG\n");
			// printf("\nDEBUG2\n");
			// debug_loop(&ghost);
			// printf("\nDEBUG2[%i]\n", ghost->status);
			if (ghost->commands && !ghost->error)
				if (shell_exec(ghost->commands, &ghost) == 0)
					return ;
			// printf("\nDEBUG3[%i]\n", ghost->status);
			// debug_loop(&ghost);
			if (ghost->status == EXECUTE)
				ghost->status = PARSE;
		}
		ghost->tokens = head;
		restart_shell(&ghost);
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
