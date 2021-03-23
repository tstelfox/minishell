/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/23 10:51:25 by tmullan       ########   odam.nl         */
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

void	init_reins(t_shell **ghost)
{
	if (!(*ghost))
		error_handler(ghost, INTERNAL_ERROR, "failed to initialize structs", NULL);
	if (!reins_key((*ghost)->reins, KEY_ESC "[" KEY_UP, up_function))
		error_handler(ghost, INTERNAL_ERROR, "failed to bind key", NULL);
	if (!reins_hook((*ghost)->reins, KEY_ESC "[" KEY_UP, &pass_param, ghost))
		error_handler(ghost, INTERNAL_ERROR, "failed to bind key", NULL);
	if (!reins_key((*ghost)->reins, KEY_ESC "[" KEY_DOWN, down_function))
		error_handler(ghost, INTERNAL_ERROR, "failed to bind key", NULL);
	if (!reins_hook((*ghost)->reins, KEY_ESC "[" KEY_DOWN, &pass_param, ghost))
		error_handler(ghost, INTERNAL_ERROR, "failed to bind key", NULL);
}

void	exec_shell(char *envp[])
{
	char	*input;
	t_shell *ghost;

	ghost = init_shell(envp);
	init_reins(&ghost);
	// // ---------env---------
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
		ghost->first_command = TRUE;// for storing the first command in history;
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
		read_line(&ghost, &input);
		lexer(&ghost, input);
		if (ghost->status == 0)
			parser(&ghost);
		debug_loop(&ghost);
		if (shell_exec(ghost->commands, ghost) == 0)
			break;
		free(input);
		restart_shell(ghost);
	}
	reins_destroy(ghost->reins);
}

int	main(int argc, char *args[], char *envp[])
{
	(void)argc;
	(void)args;

	exec_shell(envp);
	return (0);
}
