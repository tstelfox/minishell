/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/05/25 18:08:37 by tmullan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	print_env(char **str)
{
	while (*str)
	{
		printf("[%s]\n", *str);
		str++;
	}
}

void	exec_shell(t_shell **ghost, t_list *head, char *line)
{
	while ((*ghost)->status != INTERNAL_ERROR)
	{
		signal(SIGINT, ctrl);
		signal(SIGQUIT, SIG_IGN);
		(*ghost)->first_command = TRUE;
		(*ghost)->red_in = -42;
		(*ghost)->red_out = -42;
		ft_putstr_fd("\e[1;34mghostshell$> \e[0m", STDERR_FILENO);
		line = read_line(ghost);
		(*ghost)->tokens = lexer(ghost, line, " ><|;");
		head = (*ghost)->tokens;
		free(line);
		while ((*ghost)->tokens)
		{
			(*ghost)->commands = parser(ghost);
			if (!(*ghost)->commands)
				break ;
			if ((*ghost)->commands && !(*ghost)->error)
				if (shell_exec((*ghost)->commands, ghost) == 0)
					return ;
			(*ghost)->error = 0;
		}
		(*ghost)->tokens = head;
		restart_shell(ghost);
	}
	reins_destroy((*ghost)->reins);
}

int	main(int argc, char *args[], char *envp[])
{
	t_shell	*ghost;
	t_list	*head;
	char	*line;

	head = NULL;
	line = NULL;
	(void)argc;
	(void)args;
	ghost = init_shell(envp);
	if (!ghost)
		error_handler(&ghost, INIT_ERROR, "failed to initialize structs", NULL);
	init_reins(&ghost);
	exec_shell(&ghost, head, line);
	return (0);
}
