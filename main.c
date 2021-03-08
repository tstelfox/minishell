/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/04 11:22:40 by tmullan       ########   odam.nl         */
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
}

void	exec_shell(char *envp[])
{
	char	*input;
	t_list	*tokens = NULL;
	t_list	*commands = NULL;
	t_shell ghost;

	ghost.status = 0;
	int i = 0;
	

	while (envp[i])
		i++;
	ghost.env = (char **)malloc(sizeof(char *) * (i + 1));
	int k = 0;
	while (envp[k])
	{
		ghost.env[k] = ft_strdup(envp[k]);
		k++;
	}
	ghost.env[k] = 0;
	// pid_t	pid;
	// int		status;
	signal(SIGINT, ctrl);

	input = NULL;
	while (1) // check for errors
	{
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
		read_line(&input);
		tokens = lexer(input);
		commands = parser(tokens);
		// ft_cmd_lstiter(commands, print_cmd);
		if (shell_exec(commands, &ghost) == 0) //Presuming that the input has been processed
			break;
		free(input);
	}
}

int	main(int argc, char *args[], char *envp[])
{
	(void)argc;
	(void)args;

	exec_shell(envp);
	return (0);
}
