/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/17 18:10:32 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	exec_shell(void)
{
	char	*input;
	t_list	*tokens = NULL;
	t_env	*env_list;

	// pid_t	pid;
	// int		status;

	env_list = ft_envnew("HOME", "/Users/codemuncher");
	input = NULL;
	while (1) // check for errors
	{
		ft_putstr_fd("ghostshell$> ", STDOUT_FILENO);
		read_line(&input);
		tokens = lexer(input);
		if (builtin_exec(tokens, env_list) == 0) //Presuming that the input has been processed
			break;
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
	}
	
}

int	main(void)
{
	// Set HOME env variable
	exec_shell();
	return (0);
}
