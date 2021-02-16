/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 19:18:46 by zenotan       #+#    #+#                 */
/*   Updated: 2021/02/15 20:14:27 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	read_line(char **input)
{
	int ret;
	
	ret = get_next_line(STDIN_FILENO, input);
	if (ret == -1)
	{
		free(*input);
		// err handler
	}
	return ;
}

int	main(void)
{
	char	*input;

	input = NULL;
	// prompt
	// printf("ghostshell$> ");
	while (1)
	{
		ft_putstr_fd("ghostshell$> ", STDOUT_FILENO);
		read_line(&input);
		//Tokenise dat shit
		
		if (builtin_exec(*tokens[]) == 0) //Presuming that the input has been processed
			break;
	}
	return (0);
}
