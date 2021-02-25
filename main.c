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

void	exec_shell(char **envp)
{
	char	*input;
	t_list	*tokens = NULL;
	t_shell ghost;

	ghost.status = 0;
	ghost.env = (char **)malloc(sizeof(envp));
	// t_env	*env_list;
	int i = 0;

	while (envp[i])
	{
		ghost.env[i] = ft_strdup(envp[i]);
		// ft_putstr_fd(envp[i], STDOUT_FILENO);
		// ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd("This is in the loop: ", 1);
		ft_putstr_fd(ghost.env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		
		i++;
	}
	ghost.env[i] = 0;
	ft_putstr_fd(ghost.env[0], STDOUT_FILENO);
	ft_putstr_fd(ghost.env[1], STDOUT_FILENO);
	ft_putstr_fd(ghost.env[2], STDOUT_FILENO);
	// for (int k = 0; ghost.env[k]; k++)
	// {
	// 	ft_putstr_fd("This is after: ", 1);
	// 	ft_putstr_fd(ghost.env[k], STDOUT_FILENO);
	// 	ft_putstr_fd("\n", STDOUT_FILENO);
	// }
	// pid_t	pid;
	// int		status;

	// Testing env variable list and it works. Gets printed by "env" built-in
	// env_list = ft_envnew("HOME", "/Users/codemuncher");
	// ft_envaddback(&env_list, ft_envnew("MUMYER", "hehe"));

	input = NULL;
	while (1) // check for errors
	{
		ft_putstr_fd("ghostshell$> ", STDOUT_FILENO);
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
