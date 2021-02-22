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
	// pid_t	pid;
	// int		status;

	input = NULL;
	while (1) // check for errors
	{
		// char	*tokens[] = {
		// 	"pwd"
		// };
		ft_putstr_fd("ghostshell$> ", STDOUT_FILENO);
		read_line(&input);
		// lexer
		tokens = lexer(input);
		// parser
		// exec  command
		// check errors
		// ft_putstr_fd("[" , STDOUT_FILENO);
		// ft_putstr_fd(input , STDOUT_FILENO);
		// ft_putstr_fd("]\n" , STDOUT_FILENO);
		if (builtin_exec(tokens) == 0) //Presuming that the input has been processed
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
	exec_shell();
	return (0);
}
