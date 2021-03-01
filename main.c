/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/03/01 22:38:34 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	exec_shell(char *envp[])
{
	char	*input;
	t_list	*tokens = NULL;
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

	input = NULL;
	while (1) // check for errors
	{
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDOUT_FILENO);
		// printf("\e[1;34mghostshell$>\e[0m");
		read_line(&input);
		tokens = lexer(input);
		if (builtin_exec(tokens, &ghost) == 0) //Presuming that the input has been processed
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
		free(input);
	}
	
}

int	main(int argc, char *args[], char *envp[])
{
	(void)argc;
	(void)args;
	// Set HOME env variable
	exec_shell(envp);
	return (0);
}
